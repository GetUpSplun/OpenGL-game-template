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

			void draw(Vec3 position, Vec2 size, Vec3 direction, float angle, GLuint texture, ColorRGB color);
			void draw(Vec3 position, Vec2 size, Vec3 direction, float angle, GLuint texture, Vec2 tiles_count, Vec2 tile_position, ColorRGB color);

			void renderBatch(GL::Shader* shader);

		private:
			GLuint VBO, VAO, EBO;
			// Vertex vertices[4000];
			std::vector<Vertex> vertices;
			std::vector<GLuint> textures;

	};

}

#endif
