#include "raylib.h"

#include "ball.h"
#include "bricks.h"
#include "console.h"
#include "player.h"
#include "powerUP.h"
#include "game.h"
#include "menu.h"
#include "options.h"
#include "gameplay.h"
#include "gameOver.h"

//CAMBIAR GETCENTERPOSITION A GETRECTANGLECENTER Y QUE TOME UN RECTANGULO
//TERMINAR DE PULIR COLISIONES
//INTENTAR CAMBIAR COLISION BOLA - PALETA se puede hacer lo mismo que en el pong
//REVISAR QUE TODO LO EXTERN SEA NECESARIO Y SINO QUE SEA STATIC, EJ OPCIONES EN MENU
//PONER TODO EN INGLES
//hacer consistente el codigo (mayus o minus en los structs)
//poner el "paused" segun screen height y width
//arreglar colision de paleta con pared
//AL CAMBIAR PANTALLA DURANTE EL JEUGO PREGUNTAR "Hacer esto reiniciara tu juego s/n"
//crear el modificador de multiplicador de ball.speed.x para la colision ball-player
//hacer constantes los dividers que no esten dentro de structs

int main(void)
{
	initConsole();
	init();

	
	while (!WindowShouldClose() && gamestate != closing)
	{
		if (gamestate == menu)
		{
			executeMenu();
		}
		if (gamestate == optionsMenu)
		{
			executeOptions();
		}
		if (gamestate == gameplay)
		{
			executeGameplay();
		}
		if (gamestate == gameOver)
		{
			executeGameOver();
		}
		if (gamestate == resetingValues)
		{
			for (int i = 0; i < brickAmmount; i++)
			{
				brick[i].exists = true;
			}
			pause = false;
			player.rectangle.x = GetScreenWidth() / 2;
			player.lives = 5;
			player.ballAttached = true;
			ball.position = { GetCenterPos(player), player.rectangle.y - ball.radius };
			gamestate = gameplay;
		}
	}
	CloseWindow();
	return 0;
}
