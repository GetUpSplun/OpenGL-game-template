#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <filesystem>
#include <string>

#include <GL/glew.h>
#include "../stb_image.h"

namespace GL {
	
	class Texture {
		public:
			static GLuint loadTexture(std::filesystem::path filepath, GLint filter_param);
			static GLuint loadTexture(std::filesystem::path filepath, GLint filter_param, GLuint slot);

		private:
			GLuint ID;

	};

}

#endif
