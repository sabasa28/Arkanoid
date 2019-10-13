#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct Player
{
	Rectangle rectangle;
	float speed;
	bool ballAttached = true;
	float centerPosition;
	int vidas;
};
extern Player player;
enum Scorestate
{
	lost,
	won,
	playing
};
extern Scorestate scorestate;

void initPlayer();

#endif // PLAYER_H