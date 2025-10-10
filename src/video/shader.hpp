#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

namespace GL {

	class Shader {
		public:
			Shader(std::string vertex_shader_filepath, std::string fragment_shader_filepath);
			~Shader();

			GLuint getID() {
				return ID;
			}

			void bind();
			void unbind();

		private:
			GLuint ID;

	};

}

#endif
