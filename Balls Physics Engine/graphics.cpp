#include "const.h"

void clearScreen(SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void renderBalls() {
	clearScreen(BLACK);

	for (Ball* b : balls) {
		b->render();
	}
	holding->renderGhost();
}