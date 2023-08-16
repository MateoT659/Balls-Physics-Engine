#include "const.h"

//UNITS SPACE: x: [0, ~17.7], y: [0, 10], each unit rep. 1 meter

int running = 1;
std::vector<Ball*> balls;
Ball* holding;
State currentState;

int main() {
	SDL_Event event;
	initSDL();
	currentState = SETBALLS;
	
	holding = new Ball(10, 10, 20, &YELLOW);

	while (running) {
		updateDeltaTime();

		//input
		while (SDL_PollEvent(&event)) {
			parseInput(&event);
		}
		
		//update
		if (currentState == RUNNING) {
			updateBalls();
		}

		//caps FPS
		wait();

		//render
		render();
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}