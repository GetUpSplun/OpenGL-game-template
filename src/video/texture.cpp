#include "texture.hpp"

GLuint GL::Texture::loadTexture(std::filesystem::path filepath, GLint filter_param, GLenum format) {
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

		glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, bytes);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
