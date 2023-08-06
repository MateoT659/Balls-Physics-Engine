#pragma once
#include "const.h"

class Ball
{
private:
	int radius, mass;
	float xPos, yPos, xVel, yVel, xAcc, yAcc; //in game units (meters basically)
	const SDL_Color* color;

public:
	Ball(float x, float y, int radius, int mass, const SDL_Color*);
	
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
	void setRadius(int);
	int getRadius();
	void setMass(int);
	int getMass();

	void updatePos();

	void renderGhost();
	void render();
	void renderSkeleton();
};

