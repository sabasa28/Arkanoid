#include "ball.h"

#include "raylib.h"

#include "general_elements/console.h"
namespace arkanoid_IDG {
	Ball ball;

	void initBall() {
		ball.sizeState = normalSize;
		ball.radiusDivider = 125.0f;
		ball.launchSpeedDiv.x = 0.0f;
		ball.launchSpeedDiv.y = -90.0f;
		ball.speedX1Div = 1600.0f;
		ball.speedX2Div = 800.0f;
		ball.speedX3Div = 400.0f;
		ball.speedX4Div = 266.66f;
		ball.speedX5Div = 200.0f;
		ball.speedX6Div = 160.0f;
		ball.generalYSpeedDiv = -90;
		ball.position = { static_cast<float>(screenWidth) / 2,static_cast<float>(screenHeight) / 2 };
		ball.speed = { 0.0f,0.0f };
		ball.radius = (screenWidth + screenHeight) / ball.radiusDivider;
		ball.originalRadius = (screenWidth + screenHeight) / ball.radiusDivider;
		ball.speedX0 = 0;
		ball.speedX1 = screenWidth / ball.speedX1Div;
		ball.speedX2 = screenWidth / ball.speedX2Div;
		ball.speedX3 = screenWidth / ball.speedX3Div;
		ball.speedX4 = screenWidth / ball.speedX4Div;
		ball.speedX5 = screenWidth / ball.speedX5Div;
		ball.speedX6 = screenWidth / ball.speedX6Div;
		ball.generalYSpeed = screenHeight / ball.generalYSpeedDiv;
		ball.launchSpeed.x = ball.speedX0;
		ball.launchSpeed.y = ball.generalYSpeed;
		ball.invertY = false;
		ball.invertX = false;
	}

	void initResizedBall(float multiplierX, float muliplierY, float multiplierXY)
	{
		ball.position = { ball.position.x*multiplierX,ball.position.y*muliplierY };
		ball.speed = { ball.speed.x*multiplierX,ball.speed.y*muliplierY };
		ball.radius = ball.radius*multiplierXY;
		ball.originalRadius = (screenWidth + screenHeight) / ball.radiusDivider;
		ball.speedX1 = screenWidth / ball.speedX1Div;
		ball.speedX2 = screenWidth / ball.speedX2Div;
		ball.speedX3 = screenWidth / ball.speedX3Div;
		ball.speedX4 = screenWidth / ball.speedX4Div;
		ball.speedX5 = screenWidth / ball.speedX5Div;
		ball.speedX6 = screenWidth / ball.speedX6Div;
		ball.generalYSpeed = screenHeight / ball.generalYSpeedDiv;
		ball.launchSpeed.x = ball.speedX0;
		ball.launchSpeed.y = ball.generalYSpeed;
	}

	bool ballIsOffScreenLimits(Ball ball)
	{
		if ((ball.position.x + ball.radius >= (GetScreenWidth()) && ball.speed.x > 0) || (ball.position.x <= ball.radius && ball.speed.x < 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	float ballTopSideY(Ball ball)
	{
		return ball.position.y - ball.radius;
	}

	float ballBottomSideY(Ball ball)
	{
		return ball.position.y + ball.radius;
	}

	float ballLeftSideX(Ball ball)
	{
		return ball.position.x - ball.radius;
	}

	float ballRightSideX(Ball ball)
	{
		return ball.position.x + ball.radius;
	}
}