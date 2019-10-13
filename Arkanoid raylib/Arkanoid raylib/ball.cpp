#include "ball.h"

#include "raylib.h"

#include "console.h"

Ball ball;

void initBall() {
	ball.radiusDivider = 125.0f;
	ball.launchSpeedDiv.x = 0.0f;
	ball.launchSpeedDiv.y = -90.0f;
	ball.position = { static_cast<float>(screenWidth) / 2,static_cast<float>(screenHeight) / 2 };
	ball.speed = { 0.0f,0.0f };
	ball.radius = (screenWidth + screenHeight) / ball.radiusDivider;
	ball.launchSpeed.x = 0.0f;
	ball.launchSpeed.y = screenHeight / ball.launchSpeedDiv.y;
	ball.invertY = false;
	ball.invertX = false;
}