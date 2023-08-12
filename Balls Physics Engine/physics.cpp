#include "const.h"

void applyForces(Ball* ball, Ball* other) {
	Vec2 norm = ball->pos - other->pos;
	Vec2 tang = norm.getPerp();

	Vec2 ballVNorm = ball->vel.getProjectionOn(norm);
	Vec2 otherVNorm = other->vel.getProjectionOn(norm);

	ball->vel += otherVNorm * (other->getMass()/ball->getMass()) - ballVNorm;
	other->vel += ballVNorm * (ball->getMass()/other->getMass()) - otherVNorm;
}

void ridOverlap(Ball* ball, Ball* other) {
	Vec2 change= ball->getPixelPos() - other->getPixelPos();
	
	double dist = change.mag();
	double error = ball->getRadius() + other->getRadius() - dist;

	double ratio = error / dist;

	change *= ratio/2;
	
	ball->setPixelPos(ball->getPixelPos() + change);
	other->setPixelPos(other->getPixelPos() - change);
}


void handleCollision(Ball* ball, Ball* other) {
	ridOverlap(ball, other);

	applyForces(ball, other);
}