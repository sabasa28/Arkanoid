#include "player.h"

Player player;
Scorestate scorestate;

void initPlayer() 
{
	player.rectangle.width = 100;
	player.rectangle.height = 10;
	player.rectangle.x = GetScreenWidth() / 2;
	player.rectangle.y = GetScreenHeight() - player.rectangle.height * 2;
	player.speed = 5;
	player.vidas = 5;
}