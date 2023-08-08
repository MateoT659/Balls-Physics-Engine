#include "Ball.h"

Ball::Ball(float x, float y, int rad, const SDL_Color* color) {
	this->xPos = x;
	this->yPos = y;
	if (rad < 10) {
		radius = 10;
	}
	else if (rad > 80) {
		radius = 80;
	}
	else {
		this->radius = rad;
	}
	this->mass = (radius*radius)/50;
	
	this->color = color;

	xVel = 0; yVel = 0; xAcc = 2; yAcc = -G;
}

void Ball::setPos(float x, float y) {
	this->xPos = x;
	this->yPos = y;
}
void Ball::setPixelPos(int x, int y) {
	this->xPos = (x * (float)UNIT_WIDTH / SCREEN_WIDTH);
	this->yPos = UNIT_HEIGHT - (y * (float)UNIT_HEIGHT / SCREEN_HEIGHT);
}
float Ball::getX() {
	return xPos;
}
float Ball::getY() {
	return yPos;
}
float* Ball::getXptr() {
	return &xPos;
}
float* Ball::getYptr() {
	return &yPos;
}
int Ball::getPixelX() {
	return (int)(xPos * SCREEN_WIDTH / UNIT_WIDTH) ;
}
int Ball::getPixelY() {
	return SCREEN_HEIGHT - (int)(yPos * SCREEN_HEIGHT / UNIT_HEIGHT) ;
}
float Ball::getXVelocity(){
	return xVel;
}
float Ball::getXAcceleration() {
	return xAcc;
}
float Ball::getYVelocity() {
	return yVel;
}
float Ball::getYAcceleration() {
	return yAcc;
}

int Ball::getRadius() {
	return radius;
}
int Ball::getMass() {
	return mass;
}
void Ball::setSize(int radius) {
	//radius to mass: 1/50 r^2 = m
	if (radius >= 10 && radius<80) {
		this->radius = radius;
		this->mass = (radius * radius) / 50;
	}
}

const SDL_Color* Ball::getColor() {
	return color;
}
void Ball::setColor(const SDL_Color* color) {
	this->color = color;
}

void Ball::renderGhost() {

	int x = getPixelX();
	int y = getPixelY();

	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 100);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}
void Ball::render() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
	
	int x = getPixelX();
	int y = getPixelY();

	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}
void Ball::renderSkeleton() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

	int x = getPixelX();
	int y = getPixelY();

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

void Ball::updatePos() {


	xVel += xAcc * deltaTime;
	yVel += yAcc * deltaTime;

	xPos += xVel * deltaTime;
	yPos += yVel * deltaTime;


	handleCollision();
}

void Ball::handleCollision() {
	int x = getPixelX();
	int y = getPixelY();

	if (x - radius < 0) {
		setPixelPos(radius, getPixelY());
		xVel = -xVel;
	}
	else if (x + radius > SCREEN_WIDTH) {
		setPixelPos(SCREEN_WIDTH - radius, getPixelY());
		xVel = -xVel;
	}

	if (y - radius < 0) {
		setPixelPos(getPixelX(), radius);
		yVel = -yVel;
	}
	else if (y + radius > SCREEN_HEIGHT) {
		setPixelPos(getPixelX(), SCREEN_HEIGHT - radius);
		yVel = -yVel;
	}

}