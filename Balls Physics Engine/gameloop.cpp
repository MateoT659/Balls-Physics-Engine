#include "const.h"

const int MAXFPS = 60;

const int MILLIPERFRAME = 1000 / MAXFPS;

float deltaTime = 1/MAXFPS; //the amount of time in seconds between the last frame and the current frame

int prevTime = 0, currTime = SDL_GetTicks();

void updateDeltaTime() {
	prevTime = currTime;
	currTime = SDL_GetTicks();

	deltaTime = (currTime - prevTime)/(float)1000;
}

void wait() {
	//if the amount of time since the last frame is less than the max fps, this function waits that long until rendering.
	if(SDL_GetTicks() - currTime<MILLIPERFRAME) {
		SDL_Delay(MILLIPERFRAME - (SDL_GetTicks() - currTime));
	}
}