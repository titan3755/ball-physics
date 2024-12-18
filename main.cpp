#include <circle.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL.h>
#undef main // SDL defines main, so we need to undefine it
#include <SDL_image.h>
#include <SDL_ttf.h>

constexpr auto SCREEN_WIDTH = 1280;
constexpr auto SCREEN_HEIGHT = 720;

bool checkIfMouseIsWithinWindowAndLeftMouseButtonIsPressed(SDL_Window* window) {
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	Uint32 windowFlags = SDL_GetWindowFlags(window);
	return (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && (windowFlags & SDL_WINDOW_MOUSE_FOCUS) && (windowFlags & SDL_WINDOW_INPUT_FOCUS);
}

static void setWindowTitleAccordingToFramerateAndTimeElapsed(SDL_Window* window) {
	static int frameCount = 0;
	static Uint32 lastFrameTime = 0;
	static char title[100];

	// Increment frame count every loop
	frameCount++;

	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastFrameTime >= 1000) {  // Every second
		// Calculate FPS by dividing frames by elapsed time in seconds
		int fps = frameCount;  // FPS = frames per second
		int timeElapsedInSeconds = (currentTime - lastFrameTime) / 1000;

		// Set window title with the calculated FPS
		int succ = sprintf_s(title, "Ball_Physics | FPS: %d", fps);
		if (succ < 0) {
			std::cerr << "sprintf_s Error: " << succ << std::endl;
		}
		SDL_SetWindowTitle(window, title);

		// Reset for the next frame
		lastFrameTime = currentTime;
		frameCount = 0;
	}
}


int main(int argc, char* argv[]) {
	// program start
	std::cout << "Hello, World!" << std::endl;

	// SDL2 initialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_Init Success!" << std::endl;
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "IMG_Init Success!" << std::endl;
	}
	if (TTF_Init() != 0) {
		std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_Init Success!" << std::endl;
	}

	// SDL2 window creation
	SDL_Window* window = SDL_CreateWindow("Ball_Physics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr || !window) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateWindow Success!" << std::endl;
	}

	// SDL2 renderer creation
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr || !renderer) {
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateRenderer Success!" << std::endl;
	}

	std::vector<Circle*> circlesVec;

	// make 100 circles and move them around
	//Circle* circles[1000];
	//for (int i = 0; i < 1000; ++i) {
	//	circles[i] = new Circle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 10.0f, { (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256), 255 }, renderer);
	//}

	//// vector of circles
	//for (int i = 0; i < 1000; ++i) {
	//	circlesVec.push_back(new Circle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 10.0f, { (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256), 255 }, renderer));
	//}

	// SDL2 event loop
	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		// set window title according to framerate and time elapsed
		setWindowTitleAccordingToFramerateAndTimeElapsed(window);

		// SDL2 render
		if (checkIfMouseIsWithinWindowAndLeftMouseButtonIsPressed(window)) {
			circlesVec.push_back(new Circle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 10.0f, { (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256), 255 }, renderer));
		}

		// clear the screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		 /*render location*/
		for (int i = 0; i < circlesVec.size(); ++i) {
			circlesVec[i]->draw();
		}

		// present the screen
		SDL_RenderPresent(renderer);

		// errors
		if (SDL_GetError() != nullptr && SDL_GetError()[0] != '\0') {
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		}
	}

	// SDL2 cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	// program end
	std::cout << "Goodbye, World!" << std::endl;

	return 0;
}