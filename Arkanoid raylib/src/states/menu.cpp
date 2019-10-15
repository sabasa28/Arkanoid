#include "menu.h"

#include "raylib.h"

#include "general_elements/console.h"
#include "general_elements/codingTools.h"
#include "states/game.h"
#include "assets/images.h"
#include "assets/sound.h"
namespace arkanoid_IDG {
	static Button playbutton;
	static Button optionsbutton;
	static Button exitbutton;
	static Button infobutton;
	static int optionCounterMenu = 4;
	static bool controls = false;
	static float controlsFontDiv = 15.0f;
	static int controlsFont;
	static float controlsXDiv = 8.0f;
	static float controls1YDiv = 6.0f;
	static float controls2YDiv = 3.5f;
	static float controls3YDiv = 2.5f;
	static float controls4YDiv = 1.9f;
	static float controls5YDiv = 1.25f;
	static float controls1YPos;
	static float controls2YPos;
	static float controls3YPos;
	static float controls4YPos;
	static float controls5YPos;
	static float controlsXPos;


	void initMenu()
	{
		playbutton.divider.width = 3.0f;
		playbutton.divider.height = 6.0f;
		playbutton.divider.x = 3.0f;
		playbutton.divider.y = 20.0f;
		playbutton.textFontDivider = 9.0f;
		playbutton.textDivider.x = 2.3f;
		playbutton.textDivider.y = 15.0f;
		playbutton.rectangle.width = screenWidth / playbutton.divider.width;
		playbutton.rectangle.height = screenHeight / playbutton.divider.height;
		playbutton.rectangle.x = screenWidth / playbutton.divider.x;
		playbutton.rectangle.y = screenHeight / playbutton.divider.y;
		playbutton.textFont = screenHeight / playbutton.textFontDivider;
		playbutton.textPos.x = screenWidth / playbutton.textDivider.x;
		playbutton.textPos.y = screenHeight / playbutton.textDivider.y;
		optionsbutton.divider.y = 2.2f;
		optionsbutton.textFontDivider = 9.0f;
		optionsbutton.textDivider.x = 2.6f;
		optionsbutton.textDivider.y = 2.1f;
		optionsbutton.rectangle.width = playbutton.rectangle.width;
		optionsbutton.rectangle.height = playbutton.rectangle.height;
		optionsbutton.rectangle.x = playbutton.rectangle.x;
		optionsbutton.rectangle.y = screenHeight / optionsbutton.divider.y;
		optionsbutton.textFont = screenHeight / optionsbutton.textFontDivider;
		optionsbutton.textPos.x = screenWidth / optionsbutton.textDivider.x;
		optionsbutton.textPos.y = screenHeight / optionsbutton.textDivider.y;
		exitbutton.divider.y = 1.5f;
		exitbutton.textFontDivider = 9.0f;
		exitbutton.textDivider.x = 2.3f;
		exitbutton.textDivider.y = 1.45;
		exitbutton.rectangle.width = playbutton.rectangle.width;
		exitbutton.rectangle.height = playbutton.rectangle.height;
		exitbutton.rectangle.x = playbutton.rectangle.x;
		exitbutton.rectangle.y = screenHeight / exitbutton.divider.y;
		exitbutton.textFont = screenHeight / exitbutton.textFontDivider;
		exitbutton.textPos.x = screenWidth / exitbutton.textDivider.x;
		exitbutton.textPos.y = screenHeight / exitbutton.textDivider.y;
		infobutton.divider.y = 4.0f;
		infobutton.textFontDivider = 9.0f;
		infobutton.textDivider.x = 2.75f;
		infobutton.textDivider.y = 3.7f;
		infobutton.rectangle.width = playbutton.rectangle.width;
		infobutton.rectangle.height = playbutton.rectangle.height;
		infobutton.rectangle.x = playbutton.rectangle.x;
		infobutton.rectangle.y = screenHeight / infobutton.divider.y;
		infobutton.textFont = screenHeight / infobutton.textFontDivider;
		infobutton.textPos.x = screenWidth / infobutton.textDivider.x;
		infobutton.textPos.y = screenHeight / infobutton.textDivider.y;
		controlsFont = screenHeight / controlsFontDiv;
		controls1YPos = screenHeight / controls1YDiv;
		controls2YPos = screenHeight / controls2YDiv;
		controls3YPos = screenHeight / controls3YDiv;
		controls4YPos = screenHeight / controls4YDiv;
		controls5YPos = screenHeight / controls5YDiv;
		controlsXPos = screenWidth / controlsXDiv;

	}

	void updateMenu()
	{
		UpdateMusicStream(originalMusic);
		if (controls == true)
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				controls=false;
			}
		}
		else
		{
			if (IsKeyPressed(KEY_DOWN))optionCounterMenu--;
				if (IsKeyPressed(KEY_UP))optionCounterMenu++;
				if (optionCounterMenu < 1)optionCounterMenu = 4;
				if (optionCounterMenu > 4)optionCounterMenu = 1;
				if (optionCounterMenu == 1)
				{
					playbutton.color = notSelectedOption;
					infobutton.color = notSelectedOption;
					optionsbutton.color = notSelectedOption;
					exitbutton.color = selectedOption;
					playbutton.textColor = notSelectedText;
					infobutton.textColor = notSelectedText;
					optionsbutton.textColor = notSelectedText;
					exitbutton.textColor = selectedText;
					if (IsKeyPressed(KEY_ENTER)) gamestate = closing;
				}
			if (optionCounterMenu == 2)
			{
				playbutton.color = notSelectedOption;
				infobutton.color = notSelectedOption;
				optionsbutton.color = selectedOption;
				exitbutton.color = notSelectedOption;
				playbutton.textColor = notSelectedText;
				infobutton.textColor = notSelectedText;
				optionsbutton.textColor = selectedText;
				exitbutton.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER))
				{
					lastState = menu;
					gamestate = optionsMenu;
					optionCounterMenu = 4;
				}
			}
			if (optionCounterMenu == 3)
			{
				playbutton.color = notSelectedOption;
				infobutton.color = selectedOption;
				optionsbutton.color = notSelectedOption;
				exitbutton.color = notSelectedOption;
				playbutton.textColor = notSelectedText;
				infobutton.textColor = selectedText;
				optionsbutton.textColor = notSelectedText;
				exitbutton.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER) && gamestate == menu) controls = true;
			}
			if (optionCounterMenu == 4)
			{
				playbutton.color = selectedOption;
				infobutton.color = notSelectedOption;
				optionsbutton.color = notSelectedOption;
				exitbutton.color = notSelectedOption;
				playbutton.textColor = selectedText;
				infobutton.textColor = notSelectedText;
				optionsbutton.textColor = notSelectedText;
				exitbutton.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER) && gamestate == menu) gamestate = resetingValues;
			}
		}
	}
	void drawMenu()
	{
		BeginDrawing();
		if (controls==true)
		{
			ClearBackground(BLACK);
			DrawText("CONTROLS:", controlsXPos, controls1YPos, controlsFont, WHITE);
			DrawText("Move = right and left arrows", controlsXPos, controls2YPos,controlsFont,WHITE);
			DrawText("Launch ball = spacebar", controlsXPos, controls3YPos, controlsFont, WHITE);
			DrawText("Pause = escape", controlsXPos, controls4YPos, controlsFont, WHITE);
			DrawText("Press enter to go back to menu", controlsXPos, controls5YPos, controlsFont, WHITE);
		}
		else
		{
			DrawTexture(background, 0, 0, WHITE);
			DrawRectangle(playbutton.rectangle.x, playbutton.rectangle.y, playbutton.rectangle.width, playbutton.rectangle.height, playbutton.color);
			DrawText("Play", playbutton.textPos.x, playbutton.textPos.y, playbutton.textFont, playbutton.textColor);
			DrawRectangle(infobutton.rectangle.x, infobutton.rectangle.y, infobutton.rectangle.width, infobutton.rectangle.height, infobutton.color);
			DrawText("Controls", infobutton.textPos.x, infobutton.textPos.y, infobutton.textFont, infobutton.textColor);
			DrawRectangle(optionsbutton.rectangle.x, optionsbutton.rectangle.y, optionsbutton.rectangle.width, optionsbutton.rectangle.height, optionsbutton.color);
			DrawText("Options", optionsbutton.textPos.x, optionsbutton.textPos.y, optionsbutton.textFont, optionsbutton.textColor);
			DrawRectangle(exitbutton.rectangle.x, exitbutton.rectangle.y, exitbutton.rectangle.width, exitbutton.rectangle.height, exitbutton.color);
			DrawText("Exit", exitbutton.textPos.x, exitbutton.textPos.y, exitbutton.textFont, exitbutton.textColor);
		}
		EndDrawing();
	}
}