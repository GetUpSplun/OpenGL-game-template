#include "window.hpp"

GL::Window::Window(std::string title, int screen_width, int screen_height, bool is_fullscreen): screenWidth(screen_width), screenHeight(screen_height) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Failed to initialize Window." << std::endl;
	}

	context = SDL_GL_CreateContext(window);
	if (!context) {
		std::cerr << "Failed to create context." << std::endl;
	}

	SDL_GL_MakeCurrent(window, context);

	glViewport(0, 0, screen_width, screen_height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewInit();
}

GL::Window::~Window() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void GL::Window::clear(ColorRGB color) {
	glClearColor(color.r, color.g, color.b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL::Window::swapBuffers() {
	SDL_GL_SwapWindow(window);
}

void GL::Window::setTitle(std::string title) {
	SDL_SetWindowTitle(window, title.c_str());
}
