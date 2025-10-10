#ifndef TYPE_HPP
#define TYPE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;

struct ColorRGB {
	float r;
	float g;
	float b;
};

struct ColorRGBA {
	float r;
	float g;
	float b;
	float a;
};

namespace GL {

	struct Vertex {
		GLfloat position[3];
		GLfloat color[3];
		GLfloat texCoords[2];
		GLfloat texID;
	};

}

#endif
