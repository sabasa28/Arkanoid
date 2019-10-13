#include "game.h"

#include "console.h"
#include "player.h"
#include "bricks.h"
#include "menu.h"
#include "options.h"
State gamestate = menu;

void init() 
{
	initPlayer();
	initBricks();
	initMenu();
	initOptions();
}