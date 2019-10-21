#include "player.h"

#include "general_elements/console.h"
namespace arkanoid_IDG {
	Player player;
	Scorestate scorestate;


	float getCenterXPos(Player player)
	{
		return player.centerPosition = player.rectangle.x + player.rectangle.width / 2;
	}

	

	void initPlayer()
	{
		player.divider.width = 8.0f;
		player.divider.height = 45.0f;
		player.divider.x = 2.0f;
		player.divider.y = 1.1f;
		player.speedDivider = 160.0f;
		player.rectangle.width = screenWidth / player.divider.width;
		player.rectangle.height = screenHeight / player.divider.height;
		player.rectangle.x = screenWidth / player.divider.x;
		player.rectangle.y = screenHeight / player.divider.y;
		player.speed = screenWidth / player.speedDivider;
		player.regularSpeed = player.speed;
		player.lives = 10;
		player.ballAttached = true;
	}

	void initResizedPlayer(float multiplierX, float multiplierY)
	{
		player.rectangle.width = screenWidth / player.divider.width;
		player.rectangle.height = screenHeight / player.divider.height;
		player.speed = screenWidth / player.speedDivider;
		player.rectangle.x = player.rectangle.x*multiplierX;
		player.rectangle.y = player.rectangle.y*multiplierX;
	}

}