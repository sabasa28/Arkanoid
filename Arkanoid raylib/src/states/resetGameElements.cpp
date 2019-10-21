#include "resetGameElements.h"

#include "game_elements/player.h"
#include "game_elements/ball.h"
#include "game_elements/bricks.h"
#include "states/gameplay.h"
#include "game.h"
namespace arkanoid_IDG {
	void resetGameElements() {
		initBricks();
		level = lvl1;
		for (int i = 0; i < maxBrickAmmount; i++)
		{
			if (i < lvl1BrickAmmount)
			{
				brick[i].exists = true;
			}
			else
			{
				brick[i].exists = false;
			}
		}
		player.rectangle.x = static_cast<float>(GetScreenWidth() / 2);
		player.ballAttached = true;
		pause = false;
		player.lives = 10;
		ball.position = { getCenterXPos(player), player.rectangle.y - ball.radius };
		gamestate = gameplay;
	}
}