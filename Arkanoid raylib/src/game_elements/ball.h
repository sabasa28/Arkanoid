#ifndef BALL_H
#define BALL_H

#include "raylib.h"
namespace arkanoid_IDG {
	struct Direction {
		bool left = false;
		bool right = false;
		bool down = false;
		bool up = false;
	};
	enum Size
	{
		enlarged2,
		enlarged1,
		normalSize,
		shrinked1,
		shrinked2,
	};
	struct Ball
	{
		Vector2 position;
		Vector2 speed;
		Vector2 launchSpeedDiv;
		Vector2 launchSpeed;
		float radius;
		float originalRadius;
		float radiusDivider;
		Direction generalDir;
		Size sizeState = normalSize;
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
	void initResizedBall(float multiplierX, float muliplierY, float multiplierXY);
	bool ballIsOffScreenLimits(Ball ball);
	float ballTopSideY(Ball ball);
	float ballBottomSideY(Ball ball);
	float ballLeftSideX(Ball ball);
	float ballRightSideX(Ball ball);
}
#endif // BALL_H