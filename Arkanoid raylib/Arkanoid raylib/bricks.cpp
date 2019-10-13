#include "bricks.h"
#include "raylib.h"
const int brickAmmount = 64;
int brickLines = 0;
Rectangle Brick[brickAmmount];
bool BrickExists[brickAmmount];
int bricksRemmaining = 0;

void initBricks() 
{
	for (int i = 0; i < brickAmmount; i++)
	{
		BrickExists[i] = true;
		Brick[i].height = 30;
		Brick[i].width = 40;
		Brick[i].y = 0;
		Brick[i].x = 50 * i;
		if (Brick[i].x + Brick[i].width >= GetScreenWidth())
		{
			while (Brick[i].x + Brick[i].width >= GetScreenWidth())
			{
				Brick[i].y += 40;
				Brick[i].x -= GetScreenWidth();
			}
		}
		brickLines += Brick[i].width + 10;
	}
	brickLines = brickLines / GetScreenWidth();
}