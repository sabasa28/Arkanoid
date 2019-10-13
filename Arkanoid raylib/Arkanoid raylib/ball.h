#ifndef BALL_H
#define BALL_H
#include "raylib.h"

extern Vector2 ballPosition;
extern Vector2 ballSpeed;
extern int ballRadius;
struct Bounce {
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
};
extern Bounce bounceSide;
extern bool invertY;
extern bool invertX;
#endif // BALL_H