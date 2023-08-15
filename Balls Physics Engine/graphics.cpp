#include "const.h"

void clearScreen(SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void renderBallIcon() {
	drawCircle(Vec2(42, SCREEN_HEIGHT - 42), 28, GREEN);
}

void renderVecIcon() {
	drawArrow(Vec2(20, SCREEN_HEIGHT - 20), Vec2(60, SCREEN_HEIGHT - 60), ORANGE);
}

void renderGravIcon() {
	drawArrow(Vec2(21, SCREEN_HEIGHT - 70), Vec2(63, SCREEN_HEIGHT - 14), CYAN);
	drawArrow(Vec2(63, SCREEN_HEIGHT - 70), Vec2(21, SCREEN_HEIGHT - 14), CYAN);
}

void renderIcon() {
	switch (currentState) {
	case SETBALLS:
		renderBallIcon();
		break;
	case SETFORCES:
		renderVecIcon();
		break;
	case SETGRAVITY:
		renderGravIcon();
		break;
	}
}



void drawCircle(Vec2 pos, int radius, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, (int)pos.x + dx, (int)pos.y + dy);
			}
		}
	}
}

void drawArrow(Vec2 from, Vec2 to, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

	Vec2 line = to - from;
	Vec2 lineUnit = line.getUnit();
	Vec2 linePerpUnit = lineUnit.getPerp();
	Vec2 curr = to - (lineUnit * 10);
	for (int i = 10; i > 0; i--) {

		SDL_RenderDrawLine(renderer, (int)(curr + linePerpUnit * i).x,
			(int)(curr + linePerpUnit * i).y,
			(int)(curr - linePerpUnit * i).x,
			(int)(curr - linePerpUnit * i).y);
		curr += lineUnit;
	}

	SDL_RenderDrawLine(renderer, (int)from.x, (int)from.y, (int)to.x, (int)to.y);
}

void renderBalls() {
	for (Ball* b : balls) {
		b->render();
	}
}

void render() {
	clearScreen(BLACK);
	renderBalls();

	switch (currentState) {
	case SETBALLS:
		for (Ball* b : balls) {
			b->renderVelocityVec();
		}
		holding->renderGhost();
		break;
	case SETFORCES:
		for (Ball* b : balls) {
			b->renderVelocityVec();
		}
	case SETGRAVITY:
		for (Ball* b : balls) {
			b->renderVelocityVec();
		}
	}

	renderIcon();
}

SDL_Color interpolateColors(SDL_Color from, SDL_Color to, double scale) {
	if (scale > 1 || scale < 0) return BLACK;
	double keep = 1 - scale;
	SDL_Color ret = { (Uint8)(from.r * keep + to.r * scale), (Uint8)(from.g * keep + to.g * scale), (Uint8)(from.b * keep + to.g * scale), 255 };
	return ret;
}