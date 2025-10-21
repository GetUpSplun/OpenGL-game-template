#include "text.hpp"
#include "camera.hpp"

GL::Text::Text(FT_Library ft, std::string font_path) {
	if (FT_New_Face(ft, font_path.c_str(), 0, &face)) {
		std::cerr << "Failed to load font." << std::endl;
	}

	this->setSize(48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "Failed to load Glyph." << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glBindTexture(GL_TEXTURE_2D, 0);

		GL::Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x};
		characters.insert(std::pair<char, Character>(c, character));
	}

	GLuint indices[6] = {
		0, 1, 2,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 5, nullptr, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
				glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

GL::Text::~Text() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	FT_Done_Face(face);
}

void GL::Text::draw(GL::Shader* shader, std::string text, glm::vec3 position, ColorRGB color) {
	glUseProgram(shader->getID());

	glUniform3f(glGetUniformLocation(shader->getID(), "texColor"), color.r, color.g, color.b);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		GL::Character ch = characters[*c];

		GLfloat vertices[20] = {
			position.x + ch.bearing.x, position.y - (ch.size.y - ch.bearing.y), position.z, 0.0, 1.0,
			position.x + ch.bearing.x + ch.size.x, position.y - (ch.size.y - ch.bearing.y), position.z, 1.0, 1.0,
			position.x + ch.bearing.x, position.y - (ch.size.y - ch.bearing.y) - ch.size.y, position.z, 0.0, 0.0,
			position.x + ch.bearing.x + ch.size.x, position.y - (ch.size.y - ch.bearing.y) - ch.size.y, position.z, 1.0, 0.0,
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		position.x += (ch.advance >> 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

void GL::Text::setSize(int size) {
	FT_Set_Pixel_Sizes(face, 0, size);
}
