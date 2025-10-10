#include "sprite_batch.hpp"

GL::SpriteBatch::SpriteBatch(int maxQuadCount) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, maxQuadCount * 4 * sizeof(GL::Vertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(VBO, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glEnableVertexArrayAttrib(VBO, 1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
			glEnableVertexArrayAttrib(VBO, 2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
			glEnableVertexArrayAttrib(VBO, 3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texID));

			GLuint indices[(maxQuadCount * 6)];
			int offset = 0;
			for (int i = 0; i < (maxQuadCount * 6); i += 6) {
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 1;
				indices[i + 4] = offset + 2;
				indices[i + 5] = offset + 3;

				offset += 4;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

GL::SpriteBatch::~SpriteBatch() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void GL::SpriteBatch::draw(const Vec3 position, Vec2 size, const Vec3 direction, const float angle, GLuint texture, ColorRGB color) {
	GL::Vertex v1, v2, v3, v4;

	v1.position[0] = position.x - (size.x/2);
	v1.position[1] = position.y - (size.y/2);
	v1.position[2] = position.z;

	v2.position[0] = position.x + (size.x/2);
	v2.position[1] = position.y - (size.y/2);
	v2.position[2] = position.z;

	v3.position[0] = position.x - (size.x/2);
	v3.position[1] = position.y + (size.y/2); v3.position[2] = position.z;

	v4.position[0] = position.x + (size.x/2);
	v4.position[1] = position.y + (size.y/2);
	v4.position[2] = position.z;

	v1.color[0] = v2.color[0] = v3.color[0] = v4.color[0] = color.r;
	v1.color[1] = v2.color[1] = v3.color[1] = v4.color[1] = color.g;
	v1.color[2] = v2.color[2] = v3.color[2] = v4.color[2] = color.b;

	v1.texCoords[0] = 0.0;
	v1.texCoords[1] = 1.0;

	v2.texCoords[0] = 1.0;
	v2.texCoords[1] = 1.0;

	v3.texCoords[0] = 0.0;
	v3.texCoords[1] = 0.0;

	v4.texCoords[0] = 1.0;
	v4.texCoords[1] = 0.0;

	v1.texID = v2.texID = v3.texID = v4.texID = textures.size();

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	textures.push_back(texture);
	// std::array<Vertex, 4> quad = {v1, v2, v3, v4};
	// memcpy(vertices, quad.data(), quad.size() * sizeof(Vertex));
}

void GL::SpriteBatch::draw(const Vec3 position, Vec2 size, const Vec3 direction, const float angle, GLuint texture, Vec2 tile_count, Vec2 tile_offset, ColorRGB color) {
	GL::Vertex v1, v2, v3, v4;

	v1.position[0] = position.x - (size.x/2);
	v1.position[1] = position.y - (size.y/2);
	v1.position[2] = position.z;

	v2.position[0] = position.x + (size.x/2);
	v2.position[1] = position.y - (size.y/2);
	v2.position[2] = position.z;

	v3.position[0] = position.x - (size.x/2);
	v3.position[1] = position.y + (size.y/2); v3.position[2] = position.z;

	v4.position[0] = position.x + (size.x/2);
	v4.position[1] = position.y + (size.y/2);
	v4.position[2] = position.z;

	v1.color[0] = v2.color[0] = v3.color[0] = v4.color[0] = color.r;
	v1.color[1] = v2.color[1] = v3.color[1] = v4.color[1] = color.g;
	v1.color[2] = v2.color[2] = v3.color[2] = v4.color[2] = color.b;

	v1.texCoords[0] = tile_offset.x * (1.0 / tile_count.x);
	v1.texCoords[1] = tile_offset.y * (1.0 / tile_count.y) + (1.0 / tile_count.y);

	v2.texCoords[0] = tile_offset.x * (1.0 / tile_count.x) + (1.0 / tile_count.x);
	v2.texCoords[1] = tile_offset.y * (1.0 / tile_count.y) + (1.0 / tile_count.y);

	v3.texCoords[0] = tile_offset.x * (1.0 / tile_count.x);
	v3.texCoords[1] = tile_offset.y * (1.0 / tile_count.y);

	v4.texCoords[0] = tile_offset.x * (1.0 / tile_count.x) + (1.0 / tile_count.x);
	v4.texCoords[1] = tile_offset.y * (1.0 / tile_count.y);

	v1.texID = v2.texID = v3.texID = v4.texID = textures.size();

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	textures.push_back(texture);
}

void GL::SpriteBatch::renderBatch(GL::Shader* shader) {
	glUseProgram(shader->getID());

	for (int i = 0; i < textures.size(); ++i) {
		glBindTextureUnit(i, textures[i]);
	}

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, Vec3(0.0, 0.0, 0.0));
	transform = glm::scale(transform, Vec3(1.0, 1.0, 1.0));

	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "model"), 1, GL_FALSE, glm::value_ptr(transform));

	int samplers[2] = {0, 1};
	glUniform1iv(glGetUniformLocation(shader->getID(), "textures"), 2, samplers);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

				glDrawElements(GL_TRIANGLES, 50, GL_UNSIGNED_INT, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glUseProgram(0);

	vertices.clear();
	textures.clear();
}
