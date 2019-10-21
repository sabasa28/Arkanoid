#include "gameOver.h"

#include "raylib.h"

#include "game_elements/player.h"
#include "general_elements/console.h"
#include "general_elements/codingTools.h"
#include "states/game.h"
#include "assets/sound.h"

namespace arkanoid_IDG {
	static int optionCounterGameOver = 3;
	static Vector2 result;
	static Vector2 resultDivider{ 2.8f,16.0f };
	static float resultFontDivider = 10.0f;
	static float resultFont;
	static Vector2 creditsText1Div;
	static Vector2 creditsText2Div;
	static Vector2 creditsText3Div;
	static Vector2 creditsText4Div;
	static Vector2 creditsText1;
	static Vector2 creditsText2;
	static Vector2 creditsText3;
	static Vector2 creditsText4;
	static float creditsTextFontDiv;
	static float creditsTextFont;
	static Button playAgain;
	static Button backToMenu;
	static Button exit;
	static Button credits;
	static bool showingCredits = false;

	void initGameOver()
	{
		result.x = screenWidth / resultDivider.x;
		result.y = screenHeight / resultDivider.y;
		resultFont = screenHeight / resultFontDivider;
		creditsText1Div.x = 2.3f;
		creditsText1Div.y = 6.0f;
		creditsText2Div.x = 50.0f;
		creditsText2Div.y = 3.0f;
		creditsText3Div.x = 50.0f;
		creditsText3Div.y = 2.0f;
		creditsText4Div.x = 3.0f;
		creditsText4Div.y = 1.5f;
		creditsTextFontDiv = 20.0f;
		creditsText1.x = screenWidth / creditsText1Div.x;
		creditsText1.y = screenHeight / creditsText1Div.y;
		creditsText2.x = screenWidth / creditsText2Div.x;
		creditsText2.y = screenHeight / creditsText2Div.y;
		creditsText3.x = screenWidth / creditsText3Div.x;
		creditsText3.y = screenHeight / creditsText3Div.y;
		creditsText4.x = screenWidth / creditsText4Div.x;
		creditsText4.y = screenHeight / creditsText4Div.y;
		creditsTextFont = screenHeight / creditsTextFontDiv;
		playAgain.divider.width = 3.0f;
		playAgain.divider.height = 6.0f;
		playAgain.divider.x = 3.0f;
		playAgain.divider.y = 4.75f;
		playAgain.textFontDivider = 9.0f;
		playAgain.textDivider.x = 2.98f;
		playAgain.textDivider.y = 4.3f;
		playAgain.rectangle.width = screenWidth / playAgain.divider.width;
		playAgain.rectangle.height = screenHeight / playAgain.divider.height;
		playAgain.rectangle.x = screenWidth / playAgain.divider.x;
		playAgain.rectangle.y = screenHeight / playAgain.divider.y;
		playAgain.textFont = static_cast<int>(screenHeight / playAgain.textFontDivider);
		playAgain.textPos.x = screenWidth / playAgain.textDivider.x;
		playAgain.textPos.y = screenHeight / playAgain.textDivider.y;
		backToMenu.divider.y = 2.5f;
		backToMenu.textFontDivider = 9.0f;
		backToMenu.textDivider.x = 2.4f;
		backToMenu.textDivider.y = 2.3f;
		backToMenu.rectangle.width = playAgain.rectangle.width;
		backToMenu.rectangle.height = playAgain.rectangle.height;
		backToMenu.rectangle.x = playAgain.rectangle.x;
		backToMenu.rectangle.y = screenHeight / backToMenu.divider.y;
		backToMenu.textFont = static_cast<int>(screenHeight / backToMenu.textFontDivider);
		backToMenu.textPos.x = screenWidth / backToMenu.textDivider.x;
		backToMenu.textPos.y = screenHeight / backToMenu.textDivider.y;
		exit.divider.y = 1.7f;
		exit.textFontDivider = 9.0f;
		exit.textDivider.x = 2.3f;
		exit.textDivider.y = 1.6f;
		exit.rectangle.width = playAgain.rectangle.width;
		exit.rectangle.height = playAgain.rectangle.height;
		exit.rectangle.x = playAgain.rectangle.x;
		exit.rectangle.y = screenHeight / exit.divider.y;
		exit.textFont = static_cast<int>(screenHeight / exit.textFontDivider);
		exit.textPos.x = screenWidth / exit.textDivider.x;
		exit.textPos.y = screenHeight / exit.textDivider.y;
		credits.divider.y = 1.3f;
		credits.textFontDivider = 9.0f;
		credits.textDivider.x = 2.6f;
		credits.textDivider.y = 1.25f;
		credits.rectangle.width = playAgain.rectangle.width;
		credits.rectangle.height = playAgain.rectangle.height;
		credits.rectangle.x = playAgain.rectangle.x;
		credits.rectangle.y = screenHeight / credits.divider.y;
		credits.textFont = static_cast<int>(screenHeight / credits.textFontDivider);
		credits.textPos.x = screenWidth / credits.textDivider.x;
		credits.textPos.y = screenHeight / credits.textDivider.y;
	}
	void updateGameOver()
	{
		UpdateMusicStream(originalMusic);
		if (showingCredits == false)
		{
			if (IsKeyPressed(KEY_DOWN))optionCounterGameOver--;
			if (IsKeyPressed(KEY_UP))optionCounterGameOver++;
			if (optionCounterGameOver < 0)optionCounterGameOver = 3;
			if (optionCounterGameOver > 3)optionCounterGameOver = 0;
			if (optionCounterGameOver == 0)
			{
				playAgain.color = notSelectedOption;
				backToMenu.color = notSelectedOption;
				exit.color = notSelectedOption;
				credits.color = selectedOption;
				playAgain.textColor = notSelectedText;
				backToMenu.textColor = notSelectedText;
				exit.textColor = notSelectedText;
				credits.textColor = selectedText;
				if (IsKeyPressed(KEY_ENTER))
				{
					showingCredits = true;
				}
			}
			if (optionCounterGameOver == 1)
			{
				playAgain.color = notSelectedOption;
				backToMenu.color = notSelectedOption;
				exit.color = selectedOption;
				credits.color = notSelectedOption;
				playAgain.textColor = notSelectedText;
				backToMenu.textColor = notSelectedText;
				exit.textColor = selectedText;
				credits.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER))
				{
					gamestate = closing;
				}
			}
			if (optionCounterGameOver == 2)
			{
				playAgain.color = notSelectedOption;
				backToMenu.color = selectedOption;
				exit.color = notSelectedOption;
				credits.color = notSelectedOption;
				playAgain.textColor = notSelectedText;
				backToMenu.textColor = selectedText;
				exit.textColor = notSelectedText;
				credits.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER))
				{
					gamestate = menu;
					optionCounterGameOver = 3;
					resetSounds();
				}
			}
			if (optionCounterGameOver == 3)
			{
				playAgain.color = selectedOption;
				backToMenu.color = notSelectedOption;
				exit.color = notSelectedOption;
				credits.color = notSelectedOption;
				playAgain.textColor = selectedText;
				backToMenu.textColor = notSelectedText;
				exit.textColor = notSelectedText;
				credits.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER) && gamestate == gameOver)
				{
					gamestate = resetingValues;
					resetSounds();
				}
			}
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				showingCredits = false;
			}
		}
	}
	void drawGameOver()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		if (showingCredits == false)
		{
			if (scorestate == lost)
			{
				DrawText("You lost :(", static_cast<int>(result.x), static_cast<int>(result.y), static_cast<int>(resultFont), WHITE);
			}
			if (scorestate == won)
			{
				DrawText("You won :)", static_cast<int>(result.x), static_cast<int>(result.y), static_cast<int>(resultFont), WHITE);
			}
			DrawRectangle(static_cast<int>(playAgain.rectangle.x), static_cast<int>(playAgain.rectangle.y), static_cast<int>(playAgain.rectangle.width), static_cast<int>(playAgain.rectangle.height), playAgain.color);
			DrawRectangle(static_cast<int>(backToMenu.rectangle.x), static_cast<int>(backToMenu.rectangle.y), static_cast<int>(backToMenu.rectangle.width), static_cast<int>(backToMenu.rectangle.height), backToMenu.color);
			DrawRectangle(static_cast<int>(exit.rectangle.x), static_cast<int>(exit.rectangle.y), static_cast<int>(exit.rectangle.width), static_cast<int>(exit.rectangle.height), exit.color);
			DrawRectangle(static_cast<int>(credits.rectangle.x), static_cast<int>(credits.rectangle.y), static_cast<int>(credits.rectangle.width), static_cast<int>(credits.rectangle.height), credits.color);
			DrawText("Play Again", static_cast<int>(playAgain.textPos.x), static_cast<int>(playAgain.textPos.y), static_cast<int>(playAgain.textFont), playAgain.textColor);
			DrawText("Menu", static_cast<int>(backToMenu.textPos.x), static_cast<int>(backToMenu.textPos.y), static_cast<int>(backToMenu.textFont), backToMenu.textColor);
			DrawText("Exit", static_cast<int>(exit.textPos.x), static_cast<int>(exit.textPos.y), static_cast<int>(exit.textFont), exit.textColor);
			DrawText("Credits", static_cast<int>(credits.textPos.x), static_cast<int>(credits.textPos.y), static_cast<int>(credits.textFont), credits.textColor);
		}
		else
		{
			DrawText("CREDITS", static_cast<int>(creditsText1.x), static_cast<int>(creditsText1.y), static_cast<int>(creditsTextFont), WHITE);
			DrawText("Gameplay song \"NotSoEpicSongySong\" - Micael \"BlueEagle\" Lucuman", static_cast<int>(creditsText2.x), static_cast<int>(creditsText2.y), static_cast<int>(creditsTextFont),WHITE);
			DrawText("Audio, art, design & programming - Inaki Diez Galarza", static_cast<int>(creditsText3.x), static_cast<int>(creditsText3.y), static_cast<int>(creditsTextFont), WHITE);
			DrawText("Press ENTER to go back", static_cast<int>(creditsText4.x), static_cast<int>(creditsText4.y), static_cast<int>(creditsTextFont), WHITE);
		}
		EndDrawing();
	}
}