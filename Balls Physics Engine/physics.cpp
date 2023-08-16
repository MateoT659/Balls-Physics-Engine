#include "const.h"

bool airRes = true;
bool wallCollision = true;
float gravStrength = EARTH_GRAV;
GravityDirection gravDirection = DOWN;
Vec2 gravPoint = Vec2();

void updateBalls() {
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
}

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

Vec2 pixelToGame(Vec2 coords) {
	return Vec2((coords.x * (float)UNIT_WIDTH / SCREEN_WIDTH), UNIT_HEIGHT - (coords.y * (float)UNIT_HEIGHT / SCREEN_HEIGHT));
}
Vec2 gameToPixel(Vec2 coords) {
	return Vec2((int)(coords.x * (float)SCREEN_WIDTH / UNIT_WIDTH), SCREEN_HEIGHT - (int)(coords.y * (float)SCREEN_HEIGHT / UNIT_HEIGHT));
}