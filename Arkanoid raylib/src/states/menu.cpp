#include "menu.h"

#include "raylib.h"

#include "general_elements/console.h"
#include "general_elements/codingTools.h"
#include "states/game.h"

static Button Play;
static Button Options;
static Button Exit;
int optionCounterMenu = 3;

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
	Options.divider.y = 2.2f;
	Options.textFontDivider = 9.0f;
	Options.textDivider.x = 2.6f;
	Options.textDivider.y = 2.1f;
	Options.rectangle.width = Play.rectangle.width;
	Options.rectangle.height = Play.rectangle.height;
	Options.rectangle.x = Play.rectangle.x;
	Options.rectangle.y = screenHeight / Options.divider.y;
	Options.textFont = screenHeight / Options.textFontDivider;
	Options.textPos.x = screenWidth / Options.textDivider.x;
	Options.textPos.y = screenHeight / Options.textDivider.y;
	Exit.divider.y = 1.5f;
	Exit.textFontDivider= 9.0f;
	Exit.textDivider.x = 2.3f;
	Exit.textDivider.y = 1.45;
	Exit.rectangle.width = Play.rectangle.width;
	Exit.rectangle.height = Play.rectangle.height;
	Exit.rectangle.x = Play.rectangle.x;
	Exit.rectangle.y = screenHeight / Exit.divider.y;
	Exit.textFont = screenHeight / Exit.textFontDivider;
	Exit.textPos.x = screenWidth / Exit.textDivider.x;
	Exit.textPos.y = screenHeight / Exit.textDivider.y;
}

void updateMenu()
{
	if (IsKeyPressed(KEY_DOWN))optionCounterMenu--;
	if (IsKeyPressed(KEY_UP))optionCounterMenu++;
	if (optionCounterMenu < 1)optionCounterMenu = 3;
	if (optionCounterMenu > 3)optionCounterMenu = 1;
	if (optionCounterMenu == 1)
	{
		Play.color = notSelectedOption;
		Options.color = notSelectedOption;
		Exit.color = selectedOption;
		Play.textColor = notSelectedText;
		Options.textColor = notSelectedText;
		Exit.textColor = selectedText;
		if (IsKeyPressed(KEY_ENTER)) gamestate = closing;
	}
	if (optionCounterMenu == 2)
	{
		Play.color = notSelectedOption;
		Options.color = selectedOption;
		Exit.color = notSelectedOption;
		Play.textColor = notSelectedText;
		Options.textColor = selectedText;
		Exit.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER))
		{
			lastState = menu;
			gamestate = optionsMenu;
			optionCounterMenu = 3;
		}
	}
	if (optionCounterMenu == 3)
	{
		Play.color = selectedOption;
		Options.color = notSelectedOption;
		Exit.color = notSelectedOption;
		Play.textColor = selectedText;
		Options.textColor = notSelectedText;
		Exit.textColor = notSelectedText;
		if (IsKeyPressed(KEY_ENTER) && gamestate == menu) gamestate = resetingValues;
	}
}
void drawMenu()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(Play.rectangle.x, Play.rectangle.y, Play.rectangle.width, Play.rectangle.height, Play.color);
	DrawText("Play", Play.textPos.x, Play.textPos.y, Play.textFont, Play.textColor);
	DrawRectangle(Options.rectangle.x, Options.rectangle.y, Options.rectangle.width, Options.rectangle.height, Options.color);
	DrawText("Options", Options.textPos.x, Options.textPos.y, Options.textFont, Options.textColor);
	DrawRectangle(Exit.rectangle.x, Exit.rectangle.y, Exit.rectangle.width, Exit.rectangle.height, Exit.color);
	DrawText("Exit", Exit.textPos.x, Exit.textPos.y, Exit.textFont, Exit.textColor);
	EndDrawing();
}