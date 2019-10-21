#ifndef BRICKS_H
#define BRICKS_H

#include "raylib.h"

namespace arkanoid_IDG {
	extern const int maxBrickAmmount;
	extern const int lvl1BrickAmmount;
	extern const int lvl2BrickAmmount;
	extern const int lvl3BrickAmmount;
	extern const int lvl4BrickAmmount;
	extern int brickLines;
	extern int bricksRemmaining;

	enum PowerUp
	{
		tpPlayer,
		shrinkBall,
		enlargeBall,
		slowMo,
		barrier,
		notPowerUp
	};

	struct Brick
	{
		Rectangle rectangle;
		Rectangle divider;
		bool exists;
		PowerUp content;
		Color color;
		int lives;
		bool collidedLastFrame;
	};
	extern Brick brick[];
	void initBricks();
	void initResizedBricks();
	float brickBottomSideY(Brick brick);
	float brickTopSideY(Brick brick);
	float brickLeftSideX(Brick brick);
	float brickRightSideX(Brick brick);
}
#endif // BRICKS_H