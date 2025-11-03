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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(window->getWindow(), window->getContext());
	ImGui_ImplOpenGL3_Init();

	SDL_GL_SetSwapInterval(1);
}

MainGame::~MainGame() {
	camera.reset();
	window.reset();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

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
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT) isGameRunning = false;
	}
}

void MainGame::update() {
}

void MainGame::render() {
	window->clear({0.2, 0.5, 1.0});

	renderImGui();
	window->swapBuffers();
}

void MainGame::renderImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
