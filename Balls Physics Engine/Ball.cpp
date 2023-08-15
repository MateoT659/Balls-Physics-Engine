#include "Ball.h"

Ball::Ball(float x, float y, int rad, const SDL_Color* color) {
	pos.x = x;
	pos.y = y;
	vel.x = 0;
	vel.y = 0;

	if (rad < 10) {
		radius = 10;
	}
	else if (rad > 80) {
		radius = 80;
	}
	else {
		this->radius = rad;
	}
	this->mass = radius/2.f;
	
	this->color = color;
}

void Ball::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}
void Ball::setPos(Vec2 pos) {
	this->pos = pos;
}
void Ball::setPixelPos(int x, int y) {
	pos.x = (x * (float)UNIT_WIDTH / SCREEN_WIDTH);
	pos.y = UNIT_HEIGHT - (y * (float)UNIT_HEIGHT / SCREEN_HEIGHT);
}
void Ball::setPixelPos(Vec2 pix) {
	pos.x = (pix.x * (float)UNIT_WIDTH / SCREEN_WIDTH);
	pos.y = UNIT_HEIGHT - (pix.y * (float)UNIT_HEIGHT / SCREEN_HEIGHT);
}
void Ball::pixelMoveX(int x) {
	pos.x += x * (float)UNIT_WIDTH / SCREEN_WIDTH;
} 
void Ball::pixelMoveY(int y) {
	pos.y -= y * (float)UNIT_HEIGHT / SCREEN_HEIGHT;
}

int Ball::getPixelX() {
	return (int)(pos.x * SCREEN_WIDTH / UNIT_WIDTH) ;
}
int Ball::getPixelY() {
	return SCREEN_HEIGHT - (int)(pos.y * SCREEN_HEIGHT / UNIT_HEIGHT) ;
}

Vec2 Ball::getPixelPos() {
	return Vec2((int)(pos.x * SCREEN_WIDTH / UNIT_WIDTH), SCREEN_HEIGHT - (int)(pos.y * SCREEN_HEIGHT / UNIT_HEIGHT));
}

int Ball::getRadius() {
	return radius;
}
float Ball::getMass() {
	return mass;
}
void Ball::setSize(int radius) {
	//radius to mass: r/2 = m
	if (radius >= 10 && radius<80) {
		this->radius = radius;
		this->mass = radius/2.f;
	}
}

const SDL_Color* Ball::getColor() {
	return color;
}
void Ball::setColor(const SDL_Color* color) {
	this->color = color;
}

bool Ball::isClicked(int x, int y)
{
	Vec2 pix = getPixelPos();
	Vec2 pos(x, y);

	return (pos - pix).mag2() < radius * radius;
	
}

void Ball::renderGhost() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 100);
	
	Vec2 pix = getPixelPos();

	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, (int)pix.x + dx, (int)pix.y + dy);
			}
		}
	}
}
void Ball::render() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
	
	Vec2 pix = getPixelPos();

	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, (int)pix.x + dx, (int)pix.y + dy);
			}
		}
	}
}
void Ball::renderSkeleton() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);


	Vec2 pix = getPixelPos();
	int x = (int)pix.x;
	int y  = (int)pix.y;

	int dx = radius, dy = 0;

	while (dx >= dy) {
		SDL_RenderDrawPoint(renderer, x + dx, y + dy);
		SDL_RenderDrawPoint(renderer, x + dy, y + dx);
		SDL_RenderDrawPoint(renderer, x - dx, y + dy);
		SDL_RenderDrawPoint(renderer, x - dy, y + dx);
		SDL_RenderDrawPoint(renderer, x + dx, y - dy);
		SDL_RenderDrawPoint(renderer, x + dy, y - dx);
		SDL_RenderDrawPoint(renderer, x - dx, y - dy);
		SDL_RenderDrawPoint(renderer, x - dy, y - dx);
		dy++;
		while (radius * radius < dx * dx + dy * dy) {
			dx--;
		}
	}
}

void Ball::renderVelocityVec(){ // for showing velocity vectors during RUNNING, not accurate
	double magn = vel.mag();

	if (magn == 0) return;

	double scale = (4 / -(magn + 2)) + 2;
	drawArrow(getPixelPos(), gameToPixel(pos + vel*scale/magn), interpolateColors(YELLOW, ORANGE, scale/2));
}

void Ball::updatePos() {
	
	

	vel.y += -G * deltaTime;

	vel = vel * (1 - AIR_RESISTANCE);
	if (abs(vel.x) < 0.05) {
		vel.x = 0;
	}
	if (abs(vel.y) < 0.05) {
		vel.y = 0;
	}
	pos += vel * deltaTime;

	handleWall();
}

void Ball::handleWall() {
	int x = getPixelX();
	int y = getPixelY();

	if (x - radius < 0) {
		setPixelPos(radius, getPixelY());
		vel.x *= -1;
	}
	else if (x + radius > SCREEN_WIDTH) {
		setPixelPos(SCREEN_WIDTH - radius, getPixelY());
		vel.x *= -1;
	}

	if (y - radius < 0) {
		setPixelPos(getPixelX(), radius);
		vel.y *= -1;
	}
	else if (y + radius > SCREEN_HEIGHT) {
		setPixelPos(getPixelX(), SCREEN_HEIGHT - radius);
		vel.y *= -1;
	}

}

bool Ball::collidesWith(Ball* other) {
	Vec2 dist = getPixelPos() - other->getPixelPos();
	return dist.mag2() < (radius + other->radius) * (radius + other->radius);
}
