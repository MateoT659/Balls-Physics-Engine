#pragma once
#include "const.h"

class Ball
{
private:
	int radius, mass; 
	float xPos, yPos, xVel, yVel, xAcc, yAcc; //in game units (meters basically)
	const SDL_Color* color;

public:
	Ball(float x, float y, int radius, const SDL_Color*);
	
	void setPos(float, float);
	void setPixelPos(int, int);
	float getX();
	float getY();
	float* getXptr();
	float* getYptr();
	int getPixelX();
	int getPixelY();
	float getXVelocity();
	float getYVelocity();
	float getXAcceleration();
	float getYAcceleration();
	int getRadius();
	int getMass();
	void setSize(int radius);
	const SDL_Color* getColor();
	void setColor(const SDL_Color*);

	void updatePos();
	void handleCollision();

	void renderGhost();
	void render();
	void renderSkeleton();
};

