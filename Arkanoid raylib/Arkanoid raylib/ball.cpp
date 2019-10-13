#include "ball.h"
#include "raylib.h"
Vector2 ballPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
Vector2 ballSpeed = { 0.0f, 0.0f };
int ballRadius = 10;
Bounce bounceSide;
bool invertY = false;
bool invertX = false;