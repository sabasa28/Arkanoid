#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"
extern int bricksRemmaining;
extern const int brickAmmount;
extern int brickLines;
extern Rectangle Brick[];
extern bool BrickExists[];
void initBricks();
#endif // BRICKS_H