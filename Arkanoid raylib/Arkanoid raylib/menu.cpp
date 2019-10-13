#include "menu.h"
#include "raylib.h"
#include "console.h"
#include "game.h"

Rectangle Jugar;
Rectangle Opciones;
Rectangle Salir;
int opciones = 3;
Color selectedOption = WHITE;
Color notSelectedOption = BLUE;
Color selectedText = BLUE;
Color notSelectedText = WHITE;
TextDivider playText;
TextDivider optionsText;
TextDivider exitText;

void initMenu()
{
	Jugar.width = screenWidth / 3;
	Jugar.height = screenHeight / 6;
	Jugar.x = screenWidth / 2 - Jugar.width / 2;
	Jugar.y = screenHeight / 4;
	playText.x = 2.3f;
	playText.y = 3.7f;
	playText.font = 9.0f;
	optionsText.x = 2.6f;
	optionsText.y = 2.1f;
	optionsText.font = 9.0f;
	exitText.x = 2.3f;
	exitText.y = 1.45;
	exitText.font = 9.0f;
	Opciones.width = screenWidth / 3;
	Opciones.height = screenHeight / 6;
	Opciones.x = screenWidth / 2 - Jugar.width / 2;
	Opciones.y = screenHeight / 2.2;
	Salir.width = screenWidth / 3;
	Salir.height = screenHeight / 6;
	Salir.x = screenWidth / 2 - Jugar.width / 2;
	Salir.y = screenHeight / 1.5;
}

void executeMenu()
{
	if (IsKeyPressed(KEY_DOWN))opciones--;
	if (IsKeyPressed(KEY_UP))opciones++;
	if (opciones < 1)opciones = 3;
	if (opciones > 3)opciones = 1;
	BeginDrawing();
	ClearBackground(BLACK);
	if (opciones == 1)
	{
		DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, notSelectedOption);
		DrawText("Play", screenWidth / playText.x, screenHeight / playText.y, screenHeight / playText.font, notSelectedText);
		DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, notSelectedOption);
		DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, notSelectedText);
		DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, selectedOption);
		DrawText("Salir", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, selectedText);
		if (IsKeyPressed(KEY_ENTER)) gamestate = closing;
	}
	if (opciones == 2)
	{
		DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, notSelectedOption);
		DrawText("Play", screenWidth / playText.x, screenHeight / playText.y, screenHeight / playText.font, notSelectedText);
		DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, selectedOption);
		DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, selectedText);
		DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, notSelectedOption);
		DrawText("Salir", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, notSelectedText);
		if (IsKeyDown(KEY_ENTER))
		{
			gamestate = options;
			opciones = 3;
		}
	}
	if (opciones == 3)
	{
		DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, selectedOption);
		DrawText("Play", screenWidth / playText.x, screenHeight / playText.y, screenHeight / playText.font, selectedText);
		DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, notSelectedOption);
		DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, notSelectedText);
		DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, notSelectedOption);
		DrawText("Salir", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, notSelectedText);
		if (IsKeyPressed(KEY_ENTER) && gamestate == menu) gamestate = gameplay;
	}
	EndDrawing();
}