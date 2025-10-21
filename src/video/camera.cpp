#include "camera.hpp"

GL::Camera::Camera(CameraType type, GL::Window* window, float FOVdeg, float near_plane, float far_plane) {
	switch (type) {
		case ORTHOGRAPHIC:
			projection = glm::ortho(0.0f, (float)window->getWidth(), (float)window->getHeight(), 0.0f, near_plane, far_plane);
			break;

		case PERSPECTIVE:
			projection = glm::perspective(glm::radians(FOVdeg), (float)window->getWidth()/window->getHeight(), near_plane, far_plane);
			break;
	}
}

GL::Camera::~Camera() {

}

void GL::Camera::matrix(GL::Shader* shader, std::string unif) {
	glUseProgram(shader->getID());

	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, glm::vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), unif.c_str()), 1, GL_FALSE, glm::value_ptr(projection * view));

	glUseProgram(0);
}
