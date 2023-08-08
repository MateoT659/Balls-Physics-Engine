#include "const.h"
#include "Ball.h"


/*
* GOALS: balls collision.
* 
* GOAL 2: implement basic game state swap - FIRST PROTOTYPE.
*		  collisions,  prohibit balls from being in other balls initially.
*/


//UNITS SPACE: x: [0, ~35.5], y: [0, 20]

int running = 1;
std::vector<Ball*> balls;
Ball* holding;

int main() {
	SDL_Event event;	
	initSDL();
	
	holding = new Ball(10, 10, 20, &BLUE);

	while (running) {
		//deltaTime
		updateDeltaTime();

		//input-update
		while (SDL_PollEvent(&event)) {
			parseInput(&event);
		}
		
		for (Ball* b : balls) {
			b->updatePos();
		}

		//capsFPS
		wait();

		//render
		clearScreen(BLACK);

		for (Ball* b : balls) {
			b->render();
		}
		holding->renderGhost();
		

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}