#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL.h>
#undef main // SDL defines main, so we need to undefine it
#include <SDL_image.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

	// SDL2 texture creation
	SDL_Surface* surface = IMG_Load("assets/hello.png");
	if (surface == nullptr || !surface) {
		std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "IMG_Load Success!" << std::endl;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr || !texture) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateTextureFromSurface Success!" << std::endl;
	}
	SDL_FreeSurface(surface);

	// SDL2 font creation
	TTF_Font* font = TTF_OpenFont("assets/Roboto-Regular.ttf", 24);
	if (font == nullptr || !font) {
		std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_OpenFont Success!" << std::endl;
	}
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, World!", color);
	if (textSurface == nullptr || !textSurface) {
		std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_RenderText_Solid Success!" << std::endl;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture == nullptr || !textTexture) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateTextureFromSurface Success!" << std::endl;
	}
	SDL_FreeSurface(textSurface);

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
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_Rect textRect = { 320, 240, 0, 0 };
		SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		SDL_RenderPresent(renderer);
	}

	// SDL2 cleanup
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	// program end
	std::cout << "Goodbye, World!" << std::endl;

	return 0;
}