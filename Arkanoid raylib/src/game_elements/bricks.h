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

	struct Brick
	{
		Rectangle rectangle;
		Rectangle divider;
		bool exists;
	};
	extern Brick brick[];
	void initBricks();
}
#endif // BRICKS_H