#include "raylib.h"
#include <math.h>
#include "ball.h"
#include "bricks.h"
#include "console.h"
#include "player.h"
#include "powerUP.h"
#include "game.h"
#include "menu.h"
#include "options.h"
#include "gameplay.h"

//CAMBIAR GETCENTERPOSITION A GETRECTANGLECENTER Y QUE TOME UN RECTANGULO
//TERMINAR DE PULIR COLISIONES
//INTENTAR CAMBIAR COLISION BOLA - PALETA
//AGREGAR COSAS A PANTALLA FINAL
//REVISAR QUE TODO LO EXTERN SEA NECESARIO Y SINO QUE SEA STATIC, EJ OPCIONES EN MENU
//PONER TODO EN INGLES
//cambiar el menu a como estan las opciones
//hacer consistente el codigo (mayus o minus en los structs)
//poner el "paused" segun screen height y width
//arreglar colision de paleta con pared
//arreglar posicionamiento de bloques cuando se cambia el screensize
//que la pelota empiece attacheada



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
		if (gamestate == options)
		{
			executeOptions();
		}
		if (gamestate == gameplay)
		{
			executeGameplay();
		}
		if (gamestate == finalScreen)
		{
			if (IsKeyDown('R'))gamestate = resetingValues;
			BeginDrawing();
			ClearBackground(BLUE);
			if (scorestate == lost)
			{
				DrawText("Perdiste :(", screenWidth / 3, screenHeight / 3, 50, WHITE);
			}
			if (scorestate == won)
			{
				DrawText("Ganaste :)", screenWidth / 3, screenHeight / 3, 50, WHITE);
			}
			DrawText("Presiona 'R' para jugar de nuevo B)", screenWidth / 6, screenHeight / 2, 30, WHITE);
			EndDrawing();
		}
		if (gamestate == resetingValues)
		{
			for (int i = 0; i < brickAmmount; i++)
			{
				BrickExists[i] = true;
			}
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
