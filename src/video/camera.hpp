#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "window.hpp"
#include "../type.hpp"

enum CameraType {ORTHOGRAPHIC, PERSPECTIVE};

namespace GL {
	class Camera {
		public:
			Vec3 position = Vec3(0.0, 0.0, 1.0);
			Vec3 orientation = Vec3(0.0, 0.0, -1.0);

			Camera(CameraType type, GL::Window* window, float FOVdeg, float near_plane, float far_plane);
			~Camera();

			void matrix(GL::Shader* shader, std::string unif);

		private:
			glm::mat4 projection = glm::mat4(1.0f);
	};
}

#endif
