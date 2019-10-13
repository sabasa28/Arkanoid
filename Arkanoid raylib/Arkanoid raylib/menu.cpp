#include "menu.h"
#include "raylib.h"
#include "console.h"
#include "game.h"
#include "codingTools.h"

Button Play;
Button Opciones;
Button Salir;
int optionMenu = 3;

TextDivider optionsText;
TextDivider exitText;

void initMenu()
{
	Play.divider.width = 3.0f;
	Play.divider.height = 6.0f;
	Play.divider.x = 3.0f;
	Play.divider.y = 4.0f;
	Play.textFontDivider = 9.0f;
	Play.textDivider.x = 2.3f;
	Play.textDivider.y = 3.7f;
	Play.rectangle.width = screenWidth / Play.divider.width;
	Play.rectangle.height = screenHeight / Play.divider.height;
	Play.rectangle.x = screenWidth / Play.divider.x;
	Play.rectangle.y = screenHeight / Play.divider.y;
	Play.textFont = screenHeight / Play.textFontDivider;
	Play.textPos.x = screenWidth / Play.textDivider.x;
	Play.textPos.y = screenHeight / Play.textDivider.y;
	Opciones.divider.y = 2.2f;
	Opciones.textFontDivider = 9.0f;
	Opciones.textDivider.x = 2.6f;
	Opciones.textDivider.y = 2.1f;
	Opciones.rectangle.width = Play.rectangle.width;
	Opciones.rectangle.height = Play.rectangle.height;
	Opciones.rectangle.x = Play.rectangle.x;
	Opciones.rectangle.y = screenHeight / Opciones.divider.y;
	Opciones.textFont = screenHeight / Opciones.textFontDivider;
	Opciones.textPos.x = screenWidth / Opciones.textDivider.x;
	Opciones.textPos.y = screenHeight / Opciones.textDivider.y;
	Salir.divider.y = 1.5f;
	Salir.textFontDivider= 9.0f;
	Salir.textDivider.x = 2.3f;
	Salir.textDivider.y = 1.45;
	Salir.rectangle.width = Play.rectangle.width;
	Salir.rectangle.height = Play.rectangle.height;
	Salir.rectangle.x = Play.rectangle.x;
	Salir.rectangle.y = screenHeight / Salir.divider.y;
	Salir.textFont = screenHeight / Salir.textFontDivider;
	Salir.textPos.x = screenWidth / Salir.textDivider.x;
	Salir.textPos.y = screenHeight / Salir.textDivider.y;
}

void executeMenu()
{
	if (IsKeyPressed(KEY_DOWN))optionMenu--;
	if (IsKeyPressed(KEY_UP))optionMenu++;
	if (optionMenu < 1)optionMenu = 3;
	if (optionMenu > 3)optionMenu = 1;
	if (optionMenu == 1)
	{
		Play.color = notSelectedOption;
		Opciones.color = notSelectedOption;
		Salir.color = selectedOption;
		Play.textColor = notSelectedText;
		Opciones.textColor = notSelectedText;
		Salir.textColor = selectedText;
		if (IsKeyPressed(KEY_ENTER)) gamestate = closing;
	}
	if (optionMenu == 2)
	{
		Play.color = notSelectedOption;
		Opciones.color = selectedOption;
		Salir.color = notSelectedOption;
		Play.textColor = notSelectedText;
		Opciones.textColor = selectedText;
		Salir.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER))
		{
			lastState = menu;
			gamestate = options;
			optionMenu = 3;
		}
	}
	if (optionMenu == 3)
	{
		Play.color = selectedOption;
		Opciones.color = notSelectedOption;
		Salir.color = notSelectedOption;
		Play.textColor = selectedText;
		Opciones.textColor = notSelectedText;
		Salir.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER) && gamestate == menu) gamestate = gameplay;
	}

	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(Play.rectangle.x, Play.rectangle.y, Play.rectangle.width, Play.rectangle.height, Play.color);
	DrawText("Play", Play.textPos.x, Play.textPos.y, Play.textFont, Play.textColor);
	DrawRectangle(Opciones.rectangle.x, Opciones.rectangle.y, Opciones.rectangle.width, Opciones.rectangle.height, Opciones.color);
	DrawText("Options", Opciones.textPos.x, Opciones.textPos.y, Opciones.textFont, Opciones.textColor);
	DrawRectangle(Salir.rectangle.x, Salir.rectangle.y, Salir.rectangle.width, Salir.rectangle.height, Salir.color);
	DrawText("Salir", Salir.textPos.x, Salir.textPos.y, Salir.textFont, Salir.textColor);
	EndDrawing();
}