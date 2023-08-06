#include "const.h"
#include "Ball.h"

int running = 1;

/*
* GOALS: create bounds
* 
* GOAL 2: implement basic game state swap - FIRST PROTOTYPE. place balls, scroll to change mass & size
*		  collisions, ghost ball hovering, prohibit balls from being in other balls initially.
*/


//UNITS SPACE: x: [0, ~35.5], y: [0, 20]

int main() {
	SDL_Event event;	
	initSDL();

	Ball ball(UNIT_WIDTH, 20, 50, 5, &AMETHYST);

	while (running) {
		//deltaTime
		updateDeltaTime();

		//input-update
		while (SDL_PollEvent(&event)) {
			parseInput(&event);
		}
		
		ball.updatePos();

		//capsFPS
		wait();

		//render
		clearScreen(BLACK);
		ball.render();
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}