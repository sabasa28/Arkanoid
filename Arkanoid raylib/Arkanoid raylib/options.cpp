#include "options.h"

#include "raylib.h"

#include "codingTools.h"
#include "console.h"
#include "game.h"

//Rectangle SwapScreen1;
//Rectangle SwapScreen2;
//Rectangle SwapScreen3;
//Rectangle Back;
Button MuteVolume;
Button SwapScreensize1;
Button SwapScreensize2;
Button SwapScreensize3;
Button Back;
int opcionesMenu = 5;
static Color selectedButton = WHITE;
static Color notSelectedButton = BLUE;
static Color selectedText = BLUE;
static Color notSelectedText = WHITE;
void initOptions()
{
	MuteVolume.divider.x = 3.1f;
	MuteVolume.divider.y = 5.2f;
	MuteVolume.divider.width = 2.5f;
	MuteVolume.divider.height = 6.0f;
	MuteVolume.textFontDivider = 10.0f;
	MuteVolume.textDivider.x = 2.9f;
	MuteVolume.textDivider.y = 4.5f;
	MuteVolume.rectangle.x = screenWidth / MuteVolume.divider.x;
	MuteVolume.rectangle.y = screenHeight / MuteVolume.divider.y;
	MuteVolume.rectangle.width = screenWidth / MuteVolume.divider.width;
	MuteVolume.rectangle.height = screenHeight / MuteVolume.divider.height;
	MuteVolume.textFont = screenHeight / MuteVolume.textFontDivider;
	MuteVolume.textPos.x = screenWidth / MuteVolume.textDivider.x;
	MuteVolume.textPos.y = screenHeight / MuteVolume.textDivider.y;
	SwapScreensize1.divider.x = 2.8f;
	SwapScreensize1.divider.y = 2.5f;
	SwapScreensize1.divider.width = 3.0f;
	SwapScreensize1.divider.height = 8.0f;
	SwapScreensize1.textFontDivider = 15.0f;
	SwapScreensize1.textDivider.x = 2.5f;
	SwapScreensize1.textDivider.y = 2.3f;
	SwapScreensize1.rectangle.x = screenWidth / SwapScreensize1.divider.x;
	SwapScreensize1.rectangle.y = screenHeight / SwapScreensize1.divider.y;
	SwapScreensize1.rectangle.width = screenWidth / SwapScreensize1.divider.width;
	SwapScreensize1.rectangle.height = screenHeight / SwapScreensize1.divider.height;
	SwapScreensize1.textFont = screenHeight / SwapScreensize1.textFontDivider;
	SwapScreensize1.textPos.x = screenWidth / SwapScreensize1.textDivider.x;
	SwapScreensize1.textPos.y = screenHeight / SwapScreensize1.textDivider.y;
	SwapScreensize2.divider.y = 1.8f;
	SwapScreensize2.textDivider.y = 1.7f;
	SwapScreensize2.rectangle.x = SwapScreensize1.rectangle.x;
	SwapScreensize2.rectangle.y = screenHeight / SwapScreensize2.divider.y;
	SwapScreensize2.rectangle.width = SwapScreensize1.rectangle.width;
	SwapScreensize2.rectangle.height = SwapScreensize1.rectangle.height;
	SwapScreensize2.textFont = SwapScreensize1.textFont;
	SwapScreensize2.textPos.x = SwapScreensize1.textPos.x;
	SwapScreensize2.textPos.y = screenHeight / SwapScreensize2.textDivider.y;
	SwapScreensize3.divider.y = 1.4f;
	SwapScreensize3.textDivider.y = 1.35f;
	SwapScreensize3.rectangle.x = SwapScreensize1.rectangle.x;
	SwapScreensize3.rectangle.y = screenHeight / SwapScreensize3.divider.y;
	SwapScreensize3.rectangle.width = SwapScreensize1.rectangle.width;
	SwapScreensize3.rectangle.height = SwapScreensize1.rectangle.height;
	SwapScreensize3.textFont = SwapScreensize1.textFont;
	SwapScreensize3.textPos.x = SwapScreensize1.textPos.x;
	SwapScreensize3.textPos.y = screenHeight / SwapScreensize3.textDivider.y;
	Back.divider.x = 2.5f;
	Back.divider.y = 1.17f;
	Back.textDivider.x = 2.1f;
	Back.textDivider.y = 1.13f;
	Back.divider.width = 4.0f;
	Back.rectangle.x = screenWidth / Back.divider.x;
	Back.rectangle.y = screenHeight / Back.divider.y;
	Back.rectangle.width = screenWidth / Back.divider.width;
	Back.rectangle.height = SwapScreensize1.rectangle.height;
	Back.textFont = SwapScreensize1.textFont;
	Back.textPos.x = screenWidth / Back.textDivider.x;
	Back.textPos.y = screenHeight / Back.textDivider.y;
}


void executeOptions()
{
	if (IsKeyPressed(KEY_DOWN))opcionesMenu--;
	if (IsKeyPressed(KEY_UP))opcionesMenu++;
	if (opcionesMenu < 1)opcionesMenu = 5;
	if (opcionesMenu > 5)opcionesMenu = 1;
	if (opcionesMenu == 1)
	{
		if (IsKeyPressed(KEY_ENTER)) gamestate = menu;
		MuteVolume.color = notSelectedButton;
		SwapScreensize1.color = notSelectedButton;
		SwapScreensize2.color = notSelectedButton;
		SwapScreensize3.color = notSelectedButton;
		Back.color = selectedButton;
		MuteVolume.textColor = notSelectedText;
		SwapScreensize1.textColor = notSelectedText;
		SwapScreensize2.textColor = notSelectedText;
		SwapScreensize3.textColor = notSelectedText;
		Back.textColor = selectedText;
	}
	if (opcionesMenu == 2)
	{
		MuteVolume.color = notSelectedButton;
		SwapScreensize1.color = notSelectedButton;
		SwapScreensize2.color = notSelectedButton;
		SwapScreensize3.color = selectedButton;
		Back.color = notSelectedButton;
		MuteVolume.textColor = notSelectedText;
		SwapScreensize1.textColor = notSelectedText;
		SwapScreensize2.textColor = notSelectedText;
		SwapScreensize3.textColor = selectedText;
		Back.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER))
		{
			screenWidth = GetMonitorWidth(0);
			screenHeight = GetMonitorHeight(0);
			if(GetScreenWidth()!=GetMonitorWidth(0))ToggleFullscreen();
			SetWindowSize(screenWidth, screenWidth);
			init();
		}
	}
	if (opcionesMenu == 3)
	{
		MuteVolume.color = notSelectedButton;
		SwapScreensize1.color = notSelectedButton;
		SwapScreensize2.color = selectedButton;
		SwapScreensize3.color = notSelectedButton;
		Back.color = notSelectedButton;
		MuteVolume.textColor = notSelectedText;
		SwapScreensize1.textColor = notSelectedText;
		SwapScreensize2.textColor = selectedText;
		SwapScreensize3.textColor = notSelectedText;
		Back.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER))
		{
			if (screenWidth == GetMonitorWidth(0))
			{
				ToggleFullscreen();
			}
			screenWidth = windowSize2_x;
			screenHeight = windowSize2_y;
			SetWindowSize(screenWidth, screenHeight);
			SetWindowPosition((GetMonitorWidth(0) - screenWidth) / 2, (GetMonitorHeight(0) - screenHeight) / 2);
			init();
		}
	}
	if (opcionesMenu == 4)
	{
		MuteVolume.color = notSelectedButton;
		SwapScreensize1.color = selectedButton;
		SwapScreensize2.color = notSelectedButton;
		SwapScreensize3.color = notSelectedButton;
		Back.color = notSelectedButton;
		MuteVolume.textColor = notSelectedText;
		SwapScreensize1.textColor = selectedText;
		SwapScreensize2.textColor = notSelectedText;
		SwapScreensize3.textColor = notSelectedText;
		Back.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER))
		{
			if (screenWidth == GetMonitorWidth(0))
			{
				ToggleFullscreen();
			}
			screenWidth = windowSize1_x;
			screenHeight = windowSize1_y;
			SetWindowSize(screenWidth, screenHeight);
			SetWindowPosition((GetMonitorWidth(0) - screenWidth) / 2, (GetMonitorHeight(0) - screenHeight) / 2);
			init();
		}
	}
	if (opcionesMenu == 5)
	{
		MuteVolume.color = selectedButton;
		SwapScreensize1.color = notSelectedButton;
		SwapScreensize2.color = notSelectedButton;
		SwapScreensize3.color = notSelectedButton;
		Back.color = notSelectedButton;
		MuteVolume.textColor = selectedText;
		SwapScreensize1.textColor = notSelectedText;
		SwapScreensize2.textColor = notSelectedText;
		SwapScreensize3.textColor = notSelectedText;
		Back.textColor = notSelectedText;
		SetMasterVolume(0);
	}
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(MuteVolume.rectangle.x, MuteVolume.rectangle.y, MuteVolume.rectangle.width, MuteVolume.rectangle.height, MuteVolume.color);
	DrawText("Mute sounds", MuteVolume.textPos.x, MuteVolume.textPos.y, MuteVolume.textFont, MuteVolume.textColor);
	DrawRectangle(SwapScreensize1.rectangle.x, SwapScreensize1.rectangle.y, SwapScreensize1.rectangle.width, SwapScreensize1.rectangle.height, SwapScreensize1.color);
	DrawText("Screensize 1", SwapScreensize1.textPos.x, SwapScreensize1.textPos.y, SwapScreensize1.textFont, SwapScreensize1.textColor);
	DrawRectangle(SwapScreensize2.rectangle.x, SwapScreensize2.rectangle.y, SwapScreensize2.rectangle.width, SwapScreensize2.rectangle.height, SwapScreensize2.color);
	DrawText("Screensize 2", SwapScreensize2.textPos.x, SwapScreensize2.textPos.y, SwapScreensize2.textFont, SwapScreensize2.textColor);
	DrawRectangle(SwapScreensize3.rectangle.x, SwapScreensize3.rectangle.y, SwapScreensize3.rectangle.width, SwapScreensize3.rectangle.height, SwapScreensize3.color);
	DrawText("Screensize 3", SwapScreensize3.textPos.x, SwapScreensize3.textPos.y, SwapScreensize3.textFont, SwapScreensize3.textColor);
	DrawRectangle(Back.rectangle.x, Back.rectangle.y, Back.rectangle.width, Back.rectangle.height, Back.color);
	DrawText("Back", Back.textPos.x, Back.textPos.y, Back.textFont, Back.textColor);
	EndDrawing();
}