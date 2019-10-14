#include "gameOver.h"

#include "raylib.h"

#include "game_elements/player.h"
#include "general_elements/console.h"
#include "general_elements/codingTools.h"
#include "states/game.h"

static int optionCounterGameOver = 3;
static Vector2 result;
static Vector2 resultDivider { 2.8f,16.0f };
static float resultFontDivider = 10.0f;
static float resultFont;
static Button playAgain;
static Button backToMenu;
static Button exit;
void initGameOver() 
{
	result.x = screenWidth / resultDivider.x;
	result.y = screenHeight / resultDivider.y;
	resultFont = screenHeight / resultFontDivider;
	playAgain.divider.width = 3.0f;
	playAgain.divider.height = 6.0f;
	playAgain.divider.x = 3.0f;
	playAgain.divider.y = 4.0f;
	playAgain.textFontDivider = 9.0f;
	playAgain.textDivider.x = 2.98f;
	playAgain.textDivider.y = 3.7f;
	playAgain.rectangle.width = screenWidth / playAgain.divider.width;
	playAgain.rectangle.height = screenHeight / playAgain.divider.height;
	playAgain.rectangle.x = screenWidth / playAgain.divider.x;
	playAgain.rectangle.y = screenHeight / playAgain.divider.y;
	playAgain.textFont = screenHeight / playAgain.textFontDivider;
	playAgain.textPos.x = screenWidth / playAgain.textDivider.x;
	playAgain.textPos.y = screenHeight / playAgain.textDivider.y;
	backToMenu.divider.y = 2.2f;
	backToMenu.textFontDivider = 9.0f;
	backToMenu.textDivider.x = 2.4f;
	backToMenu.textDivider.y = 2.1f;
	backToMenu.rectangle.width = playAgain.rectangle.width;
	backToMenu.rectangle.height = playAgain.rectangle.height;
	backToMenu.rectangle.x = playAgain.rectangle.x;
	backToMenu.rectangle.y = screenHeight / backToMenu.divider.y;
	backToMenu.textFont = screenHeight / backToMenu.textFontDivider;
	backToMenu.textPos.x = screenWidth / backToMenu.textDivider.x;
	backToMenu.textPos.y = screenHeight / backToMenu.textDivider.y;
	exit.divider.y = 1.5f;
	exit.textFontDivider = 9.0f;
	exit.textDivider.x = 2.3f;
	exit.textDivider.y = 1.45;
	exit.rectangle.width = playAgain.rectangle.width;
	exit.rectangle.height = playAgain.rectangle.height;
	exit.rectangle.x = playAgain.rectangle.x;
	exit.rectangle.y = screenHeight / exit.divider.y;
	exit.textFont = screenHeight / exit.textFontDivider;
	exit.textPos.x = screenWidth / exit.textDivider.x;
	exit.textPos.y = screenHeight / exit.textDivider.y;
}
void updateGameOver()
{
	if (IsKeyDown('R'))gamestate = resetingValues;
	if (IsKeyPressed(KEY_DOWN))optionCounterGameOver--;
	if (IsKeyPressed(KEY_UP))optionCounterGameOver++;
	if (optionCounterGameOver < 1)optionCounterGameOver = 3;
	if (optionCounterGameOver > 3)optionCounterGameOver = 1;
	if (optionCounterGameOver == 1)
	{
		playAgain.color = notSelectedOption;
		backToMenu.color = notSelectedOption;
		exit.color = selectedOption;
		playAgain.textColor = notSelectedText;
		backToMenu.textColor = notSelectedText;
		exit.textColor = selectedText;
		if (IsKeyPressed(KEY_ENTER)) gamestate = closing;
	}
	if (optionCounterGameOver == 2)
	{
		playAgain.color = notSelectedOption;
		backToMenu.color = selectedOption;
		exit.color = notSelectedOption;
		playAgain.textColor = notSelectedText;
		backToMenu.textColor = selectedText;
		exit.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER))
		{
			gamestate = menu;
			optionCounterGameOver = 3;
		}
	}
	if (optionCounterGameOver == 3)
	{
		playAgain.color = selectedOption;
		backToMenu.color = notSelectedOption;
		exit.color = notSelectedOption;
		playAgain.textColor = selectedText;
		backToMenu.textColor = notSelectedText;
		exit.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER) && gamestate == gameOver) gamestate = resetingValues;
	}
}
void drawGameOver() 
{
	BeginDrawing();
	ClearBackground(BLACK);
	if (scorestate == lost)
	{
		DrawText("You lost :(", result.x, result.y, resultFont, WHITE);
	}
	if (scorestate == won)
	{
		DrawText("You won :)", result.x, result.y, resultFont, WHITE);
	}
	DrawRectangle(playAgain.rectangle.x, playAgain.rectangle.y, playAgain.rectangle.width, playAgain.rectangle.height, playAgain.color);
	DrawRectangle(backToMenu.rectangle.x, backToMenu.rectangle.y, backToMenu.rectangle.width, backToMenu.rectangle.height, backToMenu.color);
	DrawRectangle(exit.rectangle.x, exit.rectangle.y, exit.rectangle.width, exit.rectangle.height, exit.color);
	DrawText("Play Again", playAgain.textPos.x, playAgain.textPos.y, playAgain.textFont, playAgain.textColor);
	DrawText("Menu", backToMenu.textPos.x, backToMenu.textPos.y, backToMenu.textFont, backToMenu.textColor);
	DrawText("Exit", exit.textPos.x, exit.textPos.y, exit.textFont, exit.textColor);
	EndDrawing();
}