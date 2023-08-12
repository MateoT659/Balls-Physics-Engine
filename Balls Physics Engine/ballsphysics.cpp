#include "const.h"


/*
* GOALS: balls collision.
* 
* GOAL 2: implement basic game state swap - FIRST PROTOTYPE.
*		  collisions,  prohibit balls from being in other balls initially.
*/


//UNITS SPACE: x: [0, ~17.7], y: [0, 10], each unit rep. 1 meter

int running = 1;
std::vector<Ball*> balls;
Ball* holding;

int main() {
	SDL_Event event;	
	initSDL();
	int c = 0;
	
	

	holding = new Ball(10, 10, 20, &GREEN);

	while (running) {
		updateDeltaTime();

		//input
		while (SDL_PollEvent(&event)) {
			parseInput(&event);
		}
		
		//update
		for (Ball* b : balls) {
			b->updatePos();
		}

		for (int i = 0; i < balls.size(); i++) {
			for (int j = i + 1; j < balls.size(); j++) {
				if (balls[i]->collidesWith(balls[j])) {
					handleCollision(balls[i], balls[j]);
				}
			}
		}

		//caps FPS
		wait();

		//render
		renderBalls();
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}