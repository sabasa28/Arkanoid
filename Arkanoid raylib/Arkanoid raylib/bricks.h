#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"

extern const int brickAmmount;
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
#endif // BRICKS_H