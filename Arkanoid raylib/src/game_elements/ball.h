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
	float speedX0;
	float speedX1;
	float speedX2;
	float speedX3;
	float speedX4;
	float speedX5;
	float speedX6;
	float speedX1Div;
	float speedX2Div;
	float speedX3Div;
	float speedX4Div;
	float speedX5Div;
	float speedX6Div;
	float generalYSpeedDiv;
	float generalYSpeed;
};
extern Ball ball;
void initBall();
#endif // BALL_H