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

	static bool showingControls = false;

	static float controlsFontDiv = 15.0f;
	static int controlsFont;
	static float controlsXDiv = 8.0f;
	static float controls1YDiv = 6.0f;
	static float controls2YDiv = 3.5f;
	static float controls3YDiv = 2.5f;
	static float controls4YDiv = 1.9f;
	static float controls5YDiv = 1.25f;
	static float controls6YDiv = 1.55f;
	static float controls1YPos;
	static float controls2YPos;
	static float controls3YPos;
	static float controls4YPos;
	static float controls5YPos;
	static float controls6YPos;
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
		playbutton.textFont = static_cast<int>(screenHeight / playbutton.textFontDivider);
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
		optionsbutton.textFont = static_cast<int>(screenHeight / optionsbutton.textFontDivider);
		optionsbutton.textPos.x = screenWidth / optionsbutton.textDivider.x;
		optionsbutton.textPos.y = screenHeight / optionsbutton.textDivider.y;
		exitbutton.divider.y = 1.5f;
		exitbutton.textFontDivider = 9.0f;
		exitbutton.textDivider.x = 2.3f;
		exitbutton.textDivider.y = 1.45f;
		exitbutton.rectangle.width = playbutton.rectangle.width;
		exitbutton.rectangle.height = playbutton.rectangle.height;
		exitbutton.rectangle.x = playbutton.rectangle.x;
		exitbutton.rectangle.y = screenHeight / exitbutton.divider.y;
		exitbutton.textFont = static_cast<int>(screenHeight / exitbutton.textFontDivider);
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
		infobutton.textFont = static_cast<int>(screenHeight / infobutton.textFontDivider);
		infobutton.textPos.x = screenWidth / infobutton.textDivider.x;
		infobutton.textPos.y = screenHeight / infobutton.textDivider.y;
		controlsFont = static_cast<int>(screenHeight / controlsFontDiv);
		controls1YPos = screenHeight / controls1YDiv;
		controls2YPos = screenHeight / controls2YDiv;
		controls3YPos = screenHeight / controls3YDiv;
		controls4YPos = screenHeight / controls4YDiv;
		controls5YPos = screenHeight / controls5YDiv;
		controls6YPos = screenHeight / controls6YDiv;
		controlsXPos = screenWidth / controlsXDiv;
	}

	void updateMenu()
	{
		UpdateMusicStream(originalMusic);

		if (showingControls == true)
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				showingControls=false;
			}
		}

		else
		{
			if (IsKeyPressed(KEY_DOWN))
			{
				optionCounterMenu--;
			}
			if (IsKeyPressed(KEY_UP))
			{
				optionCounterMenu++;
			}
			if (optionCounterMenu < 1)
			{
				optionCounterMenu = 4;
			}
			if (optionCounterMenu > 4)
			{
				optionCounterMenu = 1;
			}

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

				if (IsKeyPressed(KEY_ENTER))
				{
					gamestate = closing;
				}
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
				
				if (IsKeyPressed(KEY_ENTER) && gamestate == menu)
				{
					showingControls = true;
				}
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
				
				if (IsKeyPressed(KEY_ENTER) && gamestate == menu)
				{
					gamestate = resetingValues;
				}
			}
		}
	}

	void drawMenu()
	{
		BeginDrawing();

		if (showingControls==true)
		{
			ClearBackground(BLACK);
			DrawText("CONTROLS:", static_cast<int>(controlsXPos), static_cast<int>(controls1YPos), controlsFont, WHITE);
			DrawText("Move = right and left arrows", static_cast<int>(controlsXPos), static_cast<int>(controls2YPos),controlsFont,WHITE);
			DrawText("Launch ball = spacebar", static_cast<int>(controlsXPos), static_cast<int>(controls3YPos), controlsFont, WHITE);
			DrawText("Pause = escape", static_cast<int>(controlsXPos), static_cast<int>(controls4YPos), controlsFont, WHITE);
			DrawText("Beat all four stages to WIN!", static_cast<int>(controlsXPos), static_cast<int>(controls6YPos), controlsFont, WHITE);
			DrawText("Press enter to go back to menu", static_cast<int>(controlsXPos), static_cast<int>(controls5YPos), controlsFont, WHITE);
		}
		else
		{
			DrawTexture(background, 0, 0, WHITE);
			DrawRectangle(static_cast<int>(playbutton.rectangle.x), static_cast<int>(playbutton.rectangle.y), static_cast<int>(playbutton.rectangle.width), static_cast<int>(playbutton.rectangle.height), playbutton.color);
			DrawText("Play", static_cast<int>(playbutton.textPos.x), static_cast<int>(playbutton.textPos.y), playbutton.textFont, playbutton.textColor);
			DrawRectangle(static_cast<int>(infobutton.rectangle.x), static_cast<int>(infobutton.rectangle.y), static_cast<int>(infobutton.rectangle.width), static_cast<int>(infobutton.rectangle.height), infobutton.color);
			DrawText("Controls", static_cast<int>(infobutton.textPos.x), static_cast<int>(infobutton.textPos.y), infobutton.textFont, infobutton.textColor);
			DrawRectangle(static_cast<int>(optionsbutton.rectangle.x), static_cast<int>(optionsbutton.rectangle.y), static_cast<int>(optionsbutton.rectangle.width), static_cast<int>(optionsbutton.rectangle.height), optionsbutton.color);
			DrawText("Options", static_cast<int>(optionsbutton.textPos.x), static_cast<int>(optionsbutton.textPos.y), optionsbutton.textFont, optionsbutton.textColor);
			DrawRectangle(static_cast<int>(exitbutton.rectangle.x), static_cast<int>(exitbutton.rectangle.y), static_cast<int>(exitbutton.rectangle.width), static_cast<int>(exitbutton.rectangle.height), exitbutton.color);
			DrawText("Exit", static_cast<int>(exitbutton.textPos.x), static_cast<int>(exitbutton.textPos.y), exitbutton.textFont, exitbutton.textColor);
		}
		EndDrawing();
	}

}