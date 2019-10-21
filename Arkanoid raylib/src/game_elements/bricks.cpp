#include "bricks.h"

#include "raylib.h"

#include "general_elements/console.h"
namespace arkanoid_IDG {
	const int maxBrickAmmount = 80;
	const int lvl1BrickAmmount = 32;
	const int lvl2BrickAmmount = 48;
	const int lvl3BrickAmmount = 64;
	const int lvl4BrickAmmount = 80;
	int brickLines = 0;
	Brick brick[maxBrickAmmount];
	int bricksRemmaining = 0;
	static Vector2 offsetBricksDivider{ 80.0f,11.25f };
	void initBricks()
	{
		for (int i = 0; i < maxBrickAmmount; i++)
		{
			brick[i].divider.width = 20.0f;
			brick[i].divider.height = 15.0f;
			brick[i].divider.x = 16.0f;
			brick[i].exists = true;
			brick[i].rectangle.width = screenWidth / brick[i].divider.width;
			brick[i].rectangle.height = screenHeight / brick[i].divider.height;
			brick[i].rectangle.x = screenWidth / brick[i].divider.x * i;
			brick[i].rectangle.y = 0;
			brick[i].color = RED;
			brick[i].lives = 1;
			brick[i].collidedLastFrame = false;
			switch ((GetRandomValue(0, 30)))
			{
			case 0:
				brick[i].content = tpPlayer;
				break;
			case 7:
			case 8:
			case 9:
			case 10:
			case 1:
				brick[i].content = enlargeBall;
				break;
			case 2:
				brick[i].content = shrinkBall;
				break;
			case 3:
				brick[i].content = slowMo;
				break;
			case 4:
				brick[i].content = barrier;
				break;
			default:
				brick[i].content = notPowerUp;
			}
			switch (brick[i].content)
			{
			case tpPlayer:
				brick[i].color = ORANGE;
				break;
			case slowMo:
				brick[i].color = DARKPURPLE;
				break;
			case shrinkBall:
				brick[i].color = DARKBROWN;
				break;
			case barrier:
				brick[i].color = LIGHTGRAY;
				break;
			case enlargeBall:
				brick[i].color = YELLOW;
				break;
			case notPowerUp:
				brick[i].color = RED;
				brick[i].lives = 2;
				break;
			}
			if (brick[i].rectangle.x + brick[i].rectangle.width >= GetScreenWidth())
			{
				while (brick[i].rectangle.x + brick[i].rectangle.width >= GetScreenWidth())
				{
					brick[i].rectangle.y += screenHeight / offsetBricksDivider.y;
					brick[i].rectangle.x -= GetScreenWidth();
				}
			}
			brickLines += brick[i].rectangle.width + screenWidth / offsetBricksDivider.x;
		}
		brickLines = brickLines / GetScreenWidth();
	}

	void initResizedBricks()
	{
		for (int i = 0; i < maxBrickAmmount; i++)
		{
			brick[i].rectangle.width = screenWidth / brick[i].divider.width;
			brick[i].rectangle.height = screenHeight / brick[i].divider.height;
			brick[i].rectangle.x = screenWidth / brick[i].divider.x * i;
			brick[i].rectangle.y = 0;
			if (brick[i].rectangle.x + brick[i].rectangle.width >= GetScreenWidth())
			{
				while (brick[i].rectangle.x + brick[i].rectangle.width >= GetScreenWidth())
				{
					brick[i].rectangle.y += screenHeight / offsetBricksDivider.y;
					brick[i].rectangle.x -= GetScreenWidth();
				}
			}
			brickLines += brick[i].rectangle.width + screenWidth / offsetBricksDivider.x;
		}
	}

	float brickBottomSideY(Brick brick)
	{
		return(brick.rectangle.y + brick.rectangle.height);
	}

	float brickTopSideY(Brick brick)
	{
		return brick.rectangle.y;
	}

	float brickLeftSideX(Brick brick)
	{
		return brick.rectangle.x;
	}

	float brickRightSideX(Brick brick)
	{
		return brick.rectangle.x + brick.rectangle.width;
	}
}