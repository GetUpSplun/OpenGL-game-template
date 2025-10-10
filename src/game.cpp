#include "game.hpp"

MainGame::MainGame() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize SDL_2: " << SDL_GetError() << std::endl;
	}

	if (FT_Init_FreeType(&ft_lib)) {
		std::cerr << "Failed to initialize Freetype." << std::endl;
	}

	window = std::make_unique<GL::Window>("Window", 800, 600, false);
	camera = std::make_unique<GL::Camera>(ORTHOGRAPHIC, window.get(), 45.0, 0.1, 5.0);

	SDL_GL_SetSwapInterval(1);
}

MainGame::~MainGame() {
	camera.reset();
	window.reset();

	FT_Done_FreeType(ft_lib);

	SDL_Quit();
}

int MainGame::run(int argc, char** argv) {
	while (isGameRunning) {
		processInput();
		update();
		render();
	}

	return 0;
}

void MainGame::processInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) isGameRunning = false;
	}
}

void MainGame::update() {
}

void MainGame::render() {
	window->clear({0.2, 0.5, 1.0});

	window->swapBuffers();
}
