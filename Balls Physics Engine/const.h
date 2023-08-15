#pragma once

#include <SDL.h>
#undef main
#include <SDL_ttf.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "Vec2.h"
#include "Ball.h"

class Ball;
class Vec2;

enum State {
	SETBALLS, SETFORCES, SETGRAVITY, RUNNING
};

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;
const float RATIO = (float)SCREEN_WIDTH / SCREEN_HEIGHT;

const int UNIT_HEIGHT = 10;
const int UNIT_WIDTH = (int)(UNIT_HEIGHT * RATIO);

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;
extern float deltaTime;
extern State currentState;

extern std::vector<Ball*> balls;
extern Ball* holding;

const float G = 9.8f;
const float AIR_RESISTANCE = .002f;

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color BLACK = { 0, 0, 0, 255 };
const SDL_Color RED = { 187,0,0 ,255 };
const SDL_Color ORANGE = { 255,133,15 ,255 };
const SDL_Color YELLOW = { 255, 234, 0, 255 };
const SDL_Color GREEN = { 50,245,50 ,255 };
const SDL_Color CYAN = { 0,188,227 , 255 };
const SDL_Color BLUE = { 8,39,245, 255 };
const SDL_Color PURPLE = { 102,0,204,255 };
const SDL_Color PINK = { 255,0,127,255 };
const SDL_Color AMETHYST = { 144,99,205,255 };


//input.cpp
void initSDL();
void parseInput(SDL_Event* event);

//graphics.cpp
SDL_Color interpolateColors(SDL_Color, SDL_Color, double);
void render();
void renderIcon();
void clearScreen(SDL_Color);
void renderBalls();
void drawCircle(Vec2, int, SDL_Color);
void drawArrow(Vec2 from, Vec2 to, SDL_Color color);

//gameloop.cpp
void updateDeltaTime(void);
void wait(void);

//physics.cpp
void handleCollision(Ball*, Ball*);
Vec2 pixelToGame(Vec2);
Vec2 gameToPixel(Vec2);