#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#include <SDL2/SDL_video.h>
#include <GL/glew.h>

#include "../type.hpp"

namespace GL {

	class Window {
		public:
			Window(std::string title, int screen_width, int screen_height, bool is_fullscreen);
			~Window();

			void clear(ColorRGB color);

			void swapBuffers();

			void setTitle(std::string title);

			int getWidth() {
				return screenWidth;
			}

			int getHeight() {
				return screenHeight;
			}

		private:
			SDL_Window* window = nullptr;
			SDL_GLContext context;

			int screenWidth = 0;
			int screenHeight = 0;

	};

}

#endif
