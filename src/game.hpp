#pragma once

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "video/camera.hpp"
#include "video/window.hpp"

class MainGame {
	public:
		MainGame();
		~MainGame();

		int run(int argc, char** argv);

	private:
		bool isGameRunning = true;

		FT_Library ft_lib;

		std::unique_ptr<GL::Window> window;
		std::unique_ptr<GL::Camera> camera;

		void processInput();
		void update();
		void render();

};
