#include "game.h"

#include "console.h"
#include "player.h"
#include "bricks.h"
#include "menu.h"
#include "options.h"
#include "gameplay.h"
#include "ball.h"
#include "gameOver.h"
State gamestate = menu;
State lastState = menu;
void init() 
{
	initPlayer();
	initBall();
	initBricks();
	initMenu();
	initPause();
	initOptions();
	initGameOver();
}