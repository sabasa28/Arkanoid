#ifndef BALL_H
#define BALL_H
#include "raylib.h"

struct Bounce {
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
};
struct Ball
{
	Vector2 position;
	Vector2 speed;
	Vector2 launchSpeedDiv;
	Vector2 launchSpeed;

	float radius;
	float radiusDivider;
	Bounce bounceSide;
	bool invertY;
	bool invertX;
};
extern Ball ball;
void initBall();
#endif // BALL_H