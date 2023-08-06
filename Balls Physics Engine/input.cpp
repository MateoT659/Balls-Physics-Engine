#include "const.h"

SDL_Window* window;
SDL_Renderer* renderer;

void parseInput(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			running = 0; //exit application
		}
	}
}

void initSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	window = SDL_CreateWindow("Graph Creater", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		exit(2);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	clearScreen(BLACK);
	SDL_RenderPresent(renderer);
}