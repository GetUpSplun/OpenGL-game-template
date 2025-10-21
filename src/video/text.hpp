#ifndef TEXT_HPP
#define TEXT_HPP

#include <iostream>
#include <map>
#include <string>

#include <GL/glew.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "shader.hpp"
#include "../type.hpp"

namespace GL {

	struct Character {
		GLuint textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
	};

	class Text {
		public:
			Text(FT_Library ft, std::string font_path);
			~Text();

			void draw(GL::Shader* shader, std::string text, glm::vec3 position, ColorRGB color);
			void setSize(int size);

		private:
			FT_Face face;
			std::map<char, Character> characters;
			GLuint VAO, VBO, EBO;

	};

}

#endif
