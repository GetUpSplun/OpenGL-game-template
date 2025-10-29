#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include <iostream>
#include <vector>
#include <array>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "shader.hpp"
#include "texture.hpp"
#include "../type.hpp"

namespace GL {
	
	class SpriteBatch {
		public:
			SpriteBatch(int maxQuadCount);
			~SpriteBatch();

			void draw(glm::vec3 position, glm::vec2 size, glm::vec3 direction, float angle, GLuint texture, ColorRGB color, Shader* shader);
			void draw(glm::vec3 position, glm::vec2 size, glm::vec3 direction, float angle, GLuint texture, glm::vec2 tiles_count, glm::vec2 tile_position, ColorRGB color, Shader* shader);

			void renderBatch(GL::Shader* shader);

		private:
			GLuint VBO, VAO, EBO, texture;
			std::vector<Vertex> vertices;

	};

}

#endif
