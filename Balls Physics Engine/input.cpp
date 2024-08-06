#include "const.h"

SDL_Window* window;
SDL_Renderer* renderer;

void changeColor(SDL_Event*);
bool changeState(SDL_Event*);

void parseSetBalls(SDL_Event* event) {
	int x, y;
	switch (event->type) {
	case SDL_KEYDOWN:
		if (changeState(event)) {
			return;
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
		else if (event->button.button == SDL_BUTTON_RIGHT) {
			for (int i = 0; i < balls.size(); i++) {
				if (balls[i]->isClicked(x, y)) {
					balls.erase(balls.begin() + i);
				}
			}
		}
		break;
	case SDL_MOUSEWHEEL:
		if (event->wheel.y > 0) {
			holding->setSize((int)(1.1 * holding->getRadius()));
		}
		else if (event->wheel.y < 0) {
			holding->setSize((int)(.92 * holding->getRadius()));
		}
	}
}

void parseSetForces(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (changeState(event)) {
			return;
		}
		else{
			switch (event->key.keysym.sym) {
			case SDLK_a:
				airRes = (airRes + 1) % 3;
				break;
			case SDLK_w:
				wallCollision = !wallCollision;
				break;
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN: 
		int x, y;
		Ball* pressed = nullptr;
		SDL_GetMouseState(&x, &y);
		switch (event->button.button) {
		case SDL_BUTTON_LEFT:
			for (int i = 0; i < balls.size() && pressed == nullptr; i++) {
				if (balls[i]->isClicked(x, y)) {
					pressed = balls[i];
				}
			}
			if (pressed != nullptr) {
				while (event->type != SDL_MOUSEBUTTONUP || event->button.button != SDL_BUTTON_LEFT) {
					SDL_PollEvent(event);
				}
				SDL_GetMouseState(&x, &y);
				Vec2 end = pixelToGame(Vec2(x, y));
				pressed->vel = (end - pressed->pos)*2;
			}
			break;
		case SDL_BUTTON_RIGHT:
			for (Ball* b : balls) {
				if (b->isClicked(x, y)) {
					b->vel = Vec2();
				}
			}
			break;
		}
		break;
	}
}

void parseSetGravity(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (changeState(event)) {
			return;
		}
		else {
			switch (event->key.keysym.sym) {
			case SDLK_0:
				gravDirection = NONE;
				break;
			case SDLK_1:
				gravStrength = MOON_GRAV;
				break;
			case SDLK_2:
				gravStrength = EARTH_GRAV;
				break;
			case SDLK_3:
				gravStrength = SUN_GRAV;
				break;
			case SDLK_RIGHT:
				gravDirection = RIGHT;
				break;
			case SDLK_LEFT:
				gravDirection = LEFT;
				break;
			case SDLK_DOWN:
				gravDirection = DOWN;
				break;
			case SDLK_UP:
				gravDirection = UP;
				break;
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT) {
			gravDirection = ATTRACT;
		}
		else {
			gravDirection = REPEL;
		}
		int x, y;
		SDL_GetMouseState(&x, &y);
		gravPoint = pixelToGame(Vec2(x, y));
		break;
	}
}

void parseRunning(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_SPACE) {
			currentState = SETBALLS;
			return;
		}
		else if (changeState(event)) {
			return;
		}

	}
}

void parseInput(SDL_Event* event) {
	if (event->key.keysym.sym == SDLK_ESCAPE || event->type == SDL_QUIT) {
		running = 0; return; //check exit
	}

	switch (currentState) {
	case SETBALLS:
		int x, y;
		SDL_GetMouseState(&x, &y);
		holding->setPixelPos(x, y);
		parseSetBalls(event);
		break;
	case SETFORCES:
		parseSetForces(event);
		break;
	case SETGRAVITY:
		parseSetGravity(event);
		break;
	case RUNNING:
		parseRunning(event);
		break;
	}
}

bool changeState(SDL_Event* event) {
	switch (event->key.keysym.sym) {
	case SDLK_b:
		currentState = SETBALLS;
		return true;
	case SDLK_v:
		currentState = SETFORCES;
		return true;
	case SDLK_g:
		currentState = SETGRAVITY;
		return true;
	case SDLK_SPACE:
		currentState = RUNNING;
		return true;
	}
	return false;
}

void changeColor(SDL_Event* event) {
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