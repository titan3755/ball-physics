#include <circle.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL.h>
#undef main // SDL defines main, so we need to undefine it
#include <SDL_image.h>
#include <SDL_ttf.h>

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;

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
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr || !renderer) {
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateRenderer Success!" << std::endl;
	}

	// make 100 circles and move them around
	Circle* circles[100];
	for (int i = 0; i < 100; ++i) {
		circles[i] = new Circle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 10.0f, { (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256), 255 }, renderer);
	}
	
	// SDL2 event loop
	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		// SDL2 render

		// clear the screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// render location
		for (int i = 0; i < 100; ++i) {
			circles[i]->draw();
			circles[i]->setAcceleration({ 0.0f, 9.8f });
			circles[i]->setVelocity(circles[i]->getVelocity() + circles[i]->getAcceleration() * 0.01f);
			circles[i]->move(circles[i]->getVelocity().x, circles[i]->getVelocity().y);
			circles[i]->setPos(circles[i]->getPos().x, circles[i]->getPos().y);
			circles[i]->setRadius(10.0f);
			circles[i]->setColor({ (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256), 255 });
			circles[i]->update(0.01f);
			if (circles[i]->getPos().x < 0) {
				circles[i]->setPos(SCREEN_WIDTH, circles[i]->getPos().y);
			}
			if (circles[i]->getPos().x > SCREEN_WIDTH) {
				circles[i]->setPos(0, circles[i]->getPos().y);
			}
			if (circles[i]->getPos().y < 0) {
				circles[i]->setPos(circles[i]->getPos().x, SCREEN_HEIGHT);
			}
			if (circles[i]->getPos().y > SCREEN_HEIGHT) {
				circles[i]->setPos(circles[i]->getPos().x, 0);
			}
			if (circles[i]->getVelocity().x > 30.0f) {
				circles[i]->setVelocity(10.0f, circles[i]->getVelocity().y);
			}
			if (circles[i]->getVelocity().y > 30.0f) {
				circles[i]->setVelocity(circles[i]->getVelocity().x, 10.0f);
			}
			if (circles[i]->getAcceleration().x > 100.0f) {
				circles[i]->setAcceleration(10.0f, circles[i]->getAcceleration().y);
			}
			if (circles[i]->getAcceleration().y > 100.0f) {
				circles[i]->setAcceleration(circles[i]->getAcceleration().x, 10.0f);
			}
		}

		// present the screen
		SDL_RenderPresent(renderer);
	}

	// SDL2 cleanup
	for (int i = 0; i < 100; ++i) {
		delete circles[i];
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	// program end
	std::cout << "Goodbye, World!" << std::endl;

	return 0;
}