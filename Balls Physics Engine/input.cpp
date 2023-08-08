#include "const.h"

SDL_Window* window;
SDL_Renderer* renderer;

void changeColor(SDL_Event*);

void parseInput(SDL_Event* event) {
	int x, y;
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			running = 0; //exit application
		}
		else {
			changeColor(event);
		}
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		holding->setPixelPos(x, y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		if (event->button.button == SDL_BUTTON_LEFT) {
			balls.push_back(holding);
			holding = new Ball((float)x, (float)y, holding->getRadius(), holding->getColor());
		}
		break;
	case SDL_MOUSEWHEEL:
		if (event->wheel.y > 0) {
			holding->setSize((int)(1.1*holding->getRadius()));
		}
		else if (event->wheel.y < 0) {
			holding->setSize((int)(.92 * holding->getRadius()));
		}
	}
}

void changeColor(SDL_Event* event) {
	// exits program on spacebar, or sets color on nums 1-5

	switch (event->key.keysym.sym) {
	case SDLK_1:
		holding->setColor(&WHITE);
		break;
	case SDLK_2:
		holding->setColor(&PINK);
		break;
	case SDLK_3:
		holding->setColor(&RED);
		break;
	case SDLK_4:
		holding->setColor(&ORANGE);
		break;
	case SDLK_5:
		holding->setColor(&YELLOW);
		break;
	case SDLK_6:
		holding->setColor(&GREEN);
		break;
	case SDLK_7:
		holding->setColor(&CYAN);
		break;
	case SDLK_8:
		holding->setColor(&BLUE);
		break;
	case SDLK_9:
		holding->setColor(&PURPLE);
		break;
	case SDLK_0:
		holding->setColor(&AMETHYST);
		break;
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