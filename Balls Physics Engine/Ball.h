#pragma once
#include "const.h"

class Ball
{
public:
	Vec2 pos; //in game units (meters basically)
	Vec2 vel; 
private:
	int radius;
	float mass; 
	const SDL_Color* color;

public:
	Ball(float x, float y, int radius, const SDL_Color*);
	
	void setPos(float, float);
	void setPos(Vec2);
	void setPixelPos(int, int);
	void setPixelPos(Vec2);
	void pixelMoveX(int x);
	void pixelMoveY(int y);
	Vec2 getPixelPos();
	int getPixelX();
	int getPixelY();
	int getRadius();
	float getMass();
	void setSize(int radius);
	const SDL_Color* getColor();
	void setColor(const SDL_Color*);

	bool isClicked(int x, int y);

	void updatePos();
	void handleWall();
	bool collidesWith(Ball*);

	void renderGhost();
	void render();
	void renderSkeleton();
	void renderVelocityVec();
};