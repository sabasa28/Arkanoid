#include "game.h"

#include "game_elements/player.h"
#include "game_elements/bricks.h"
#include "game_elements/ball.h"
#include "general_elements/console.h"
#include "states/menu.h"
#include "states/options.h"
#include "states/gameplay.h"
#include "states/gameOver.h"
#include "resetGameElements.h"

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

void executeGame() 
{
	initConsole();
	init();
	while (!WindowShouldClose() && gamestate != closing)
	{
		if (gamestate == menu)
		{
			updateMenu();
			drawMenu();
		}
		if (gamestate == optionsMenu)
		{
			updateOptions();
			drawOptions();
		}
		if (gamestate == gameplay)
		{
			updateGameplay();
			drawGameplay();
		}
		if (gamestate == gameOver)
		{
			updateGameOver();
			drawGameOver();
		}
		if (gamestate == resetingValues)
		{
			resetGameElements();
		}
	}
	CloseWindow();
}