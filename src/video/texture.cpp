#include "texture.hpp"

GLuint GL::Texture::loadTexture(std::filesystem::path filepath, GLint filter_param) {
	int imgWidth, imgHeight, imgBits;
	GLuint textureID;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(filepath.c_str(), &imgWidth, &imgHeight, &imgBits, 0);

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_param);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		switch (imgBits) {
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
				break;

			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
				break;

			case 1:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, imgWidth, imgHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
				break;

			default:
				throw std::invalid_argument("Failed to load texture");
				break;

		}
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

GLuint GL::Texture::loadTexture(std::filesystem::path filepath, GLint filter_param, GLuint slot) {
	int imgWidth, imgHeight, imgBits;
	GLuint textureID;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(filepath.c_str(), &imgWidth, &imgHeight, &imgBits, 0);

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_param);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		switch (imgBits) {
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
				break;

			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
				break;

			case 1:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, imgWidth, imgHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
				break;

			default:
				throw std::invalid_argument("Failed to load texture");
				break;

		}
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
