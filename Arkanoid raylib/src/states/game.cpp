#include "game.h"

#include "game_elements/player.h"
#include "game_elements/bricks.h"
#include "game_elements/ball.h"
#include "game_elements/powerUP.h"
#include "general_elements/console.h"
#include "states/menu.h"
#include "states/options.h"
#include "states/gameplay.h"
#include "states/gameOver.h"
#include "resetGameElements.h"
#include "assets/images.h"
#include "assets/sound.h"

namespace arkanoid_IDG {

	State gamestate = menu;
	State lastState = menu;

	void generalInit()
	{
		initConsole();
		initSounds();
		HideCursor();
		initTextures();
		initPlayer();
		initBall();
		initBricks();
		initPowerUps();
		initMenu();
		initPause();
		initOptions();
		initGameOver();
	}

	void resizeInit(float multiplierX, float multiplierY, float multiplierXY)
	{
		initTextures();
		initResizedPlayer(multiplierX, multiplierY);
		initResizedBall(multiplierX, multiplierY, multiplierXY);
		initResizedBricks();
		initPowerUps();
		initMenu();
		initPause();
		initOptions();
		initGameOver();
	}

	void closeGame()
	{
		unloadSounds();
		unloadTextures();
	}

	void executeGame()
	{
		generalInit();
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

		closeGame();
		CloseWindow();
	}
}