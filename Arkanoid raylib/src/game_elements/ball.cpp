#include "ball.h"

#include "raylib.h"

#include "general_elements/console.h"

Ball ball;


void initBall() {
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