#include "gameplay.h"

#include "raylib.h"

#include "game_elements/ball.h"
#include "game_elements/bricks.h"
#include "game_elements/player.h"
#include "general_elements/console.h"
#include "general_elements/codingTools.h"
#include "states/game.h"

static Button Return;
static Button Options;
static Button Exit;

Vector2 pausedText;
Vector2 pausedTextDiv{ 2.4f,8.0f };
static int pausedTextFont;
static int pausedTextFontDiv = 15.0f;
Vector2 levelText;
Vector2 levelTextDiv{ 2.5f,1.5f};
static int levelTextFont;
static int levelTextFontDiv = 10.0f;
Vector2 livesText;
Vector2 livesTextDiv{ 20.0f,1.1f };
static int livesTextFont;
static float livesTextFontDiv = 22.5f;
bool pause = false;
static int optionCounterPause = 3;
lvl level=lvl1;
void levelTransition();
void initPause()
{
	Return.divider.width = 3.0f;
	Return.divider.height = 6.0f;
	Return.divider.x = 3.0f;
	Return.divider.y = 4.0f;
	Return.textFontDivider = 9.0f;
	Return.textDivider.x = 2.5f;
	Return.textDivider.y = 3.7f;
	Return.rectangle.width = screenWidth / Return.divider.width;
	Return.rectangle.height = screenHeight / Return.divider.height;
	Return.rectangle.x = screenWidth / Return.divider.x;
	Return.rectangle.y = screenHeight / Return.divider.y;
	Return.textFont = screenHeight / Return.textFontDivider;
	Return.textPos.x = screenWidth / Return.textDivider.x;
	Return.textPos.y = screenHeight / Return.textDivider.y;
	Options.divider.y = 2.2f;
	Options.textFontDivider = 9.0f;
	Options.textDivider.x = 2.6f;
	Options.textDivider.y = 2.1f;
	Options.rectangle.width = Return.rectangle.width;
	Options.rectangle.height = Return.rectangle.height;
	Options.rectangle.x = Return.rectangle.x;
	Options.rectangle.y = screenHeight / Options.divider.y;
	Options.textFont = screenHeight / Options.textFontDivider;
	Options.textPos.x = screenWidth / Options.textDivider.x;
	Options.textPos.y = screenHeight / Options.textDivider.y;
	Exit.divider.y = 1.5f;
	Exit.textFontDivider = 9.0f;
	Exit.textDivider.x = 2.3f;
	Exit.textDivider.y = 1.45;
	Exit.rectangle.width = Return.rectangle.width;
	Exit.rectangle.height = Return.rectangle.height;
	Exit.rectangle.x = Return.rectangle.x;
	Exit.rectangle.y = screenHeight / Exit.divider.y;
	Exit.textFont = screenHeight / Exit.textFontDivider;
	Exit.textPos.x = screenWidth / Exit.textDivider.x;
	Exit.textPos.y = screenHeight / Exit.textDivider.y;
	pausedText.x = screenWidth / pausedTextDiv.x;
	pausedText.y = screenHeight / pausedTextDiv.y;
	pausedTextFont = screenHeight / pausedTextFontDiv;
	livesText.x = screenWidth / livesTextDiv.x;
	livesText.y = screenHeight / livesTextDiv.y;
	livesTextFont = screenHeight / livesTextFontDiv;
	levelText.x = screenWidth / levelTextDiv.x;
	levelText.y = screenHeight / levelTextDiv.y;
	levelTextFont = screenHeight / levelTextFontDiv;
}

void updateGameplay() {
	if (IsKeyPressed(KEY_ESCAPE))
	{
		optionCounterPause = 3;
		pause = !pause;
	}
	if (pause == false)
	{
		if (player.rectangle.x + player.rectangle.width < screenWidth)
			if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))player.rectangle.x += player.speed;
		if (player.rectangle.x > 0)
			if (IsKeyDown(KEY_LEFT) || IsKeyDown('A')) player.rectangle.x -= player.speed;
		if (player.ballAttached == true)
			if (IsKeyPressed(KEY_SPACE))
			{
				player.ballAttached = false;
				ball.speed = { ball.launchSpeed.x, ball.launchSpeed.y };
			}
		ball.position.x += ball.speed.x/**GetFrameTime()*/;
		ball.position.y += ball.speed.y/**GetFrameTime()*/;

		if (ball.position.y + ball.radius >= GetScreenHeight())
		{
			player.ballAttached = true;
			player.lives--;
		}
		if (player.ballAttached == true)ball.position = { GetCenterPos(player), player.rectangle.y - ball.radius };
		if (ball.position.x + ball.radius >= (GetScreenWidth()) && ball.speed.x > 0) ball.speed.x *= -1.0f;
		if (ball.position.x <= ball.radius && ball.speed.x < 0) ball.speed.x *= -1.0f;
		if ((ball.position.y <= ball.radius) && ball.speed.y < 0) ball.speed.y *= -1.0f;
		if (CheckCollisionCircleRec(ball.position, ball.radius, player.rectangle))
		{
			if (ball.speed.y > 0)
			{
				ball.speed.y = ball.generalYSpeed;
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces))
				{
					ball.speed.x = -ball.speedX6;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 2) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *1)))
				{
					ball.speed.x = -ball.speedX5;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 3) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *2)))
				{
					ball.speed.x = -ball.speedX4;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 4) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *3)))
				{
					ball.speed.x = -ball.speedX3;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 5) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *4)))
				{
					ball.speed.x = -ball.speedX2;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 6) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *5)))
				{
					ball.speed.x = -ball.speedX1;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 7) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *6)))
				{
					ball.speed.x = ball.speedX1;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 8) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *7)))
				{
					ball.speed.x = ball.speedX2;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 9) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *8)))
				{
					ball.speed.x = ball.speedX3;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 10) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *9)))
				{
					ball.speed.x = ball.speedX4;
				}
				if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 11) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *10)))
				{
					ball.speed.x = ball.speedX5;
				}
				if (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces *11))
				{
					ball.speed.x = ball.speedX6;
				}
			}
		}
		for (int i = 0; i < maxBrickAmmount; i++)
		{
			if (brick[i].exists == true && CheckCollisionCircleRec(ball.position, ball.radius, brick[i].rectangle))
			{
				if (ball.speed.y < 0) {
					if ((ball.position.y - ball.radius) <= (brick[i].rectangle.y + brick[i].rectangle.height)) {
						ball.bounceSide.down = true;
						brick[i].exists = false;   // TENER UNO SOLO DE ESTOS EN EL IF GENERAL
					}
				}
				if (ball.speed.y > 0)
				{
					if ((ball.position.y + ball.radius) >= (brick[i].rectangle.y)) {
						ball.bounceSide.up = true;
						brick[i].exists = false;
					}
				}
				if (ball.speed.x < 0) {
					if ((ball.position.x - ball.radius) <= (brick[i].rectangle.x + brick[i].rectangle.width)) {
						ball.bounceSide.right = true;
						brick[i].exists = false;
					}
				}
				if (ball.speed.x > 0) {
					if ((ball.position.x + ball.radius) >= (brick[i].rectangle.x)) {
						ball.bounceSide.left = true;
						brick[i].exists = false;
					}
				}
				if (ball.bounceSide.down == true && ball.bounceSide.up == true)
				{
					if (((brick[i].rectangle.y + brick[i].rectangle.height) - (ball.position.y - ball.radius)) < ((ball.position.y + ball.radius) - (brick[i].rectangle.y))) ball.bounceSide.up = false;
					else ball.bounceSide.down = false;
				}
				if (ball.bounceSide.left == true && ball.bounceSide.right == true)
				{
					if (((brick[i].rectangle.x + brick[i].rectangle.width) - (ball.position.x - ball.radius)) < ((ball.position.x + ball.radius) - (brick[i].rectangle.x))) ball.bounceSide.right = false;
					else ball.bounceSide.left == false;
				}
				if (ball.bounceSide.down == true)
				{
					if (ball.bounceSide.left == true)
					{
						if (((brick[i].rectangle.y + brick[i].rectangle.height) - (ball.position.y - ball.radius)) < ((ball.position.x + ball.radius) - (brick[i].rectangle.x)))ball.bounceSide.left = false;
						else ball.bounceSide.down = false;

					}
					if (ball.bounceSide.right == true)
					{
						if (((brick[i].rectangle.y + brick[i].rectangle.height) - (ball.position.y - ball.radius)) < ((brick[i].rectangle.x + brick[i].rectangle.width) - (ball.position.x - ball.radius)))ball.bounceSide.right = false;
						else ball.bounceSide.down = false;
					}
				}
				if (ball.bounceSide.up == true)
				{
					if (ball.bounceSide.left == true)
					{
						if (((ball.position.y + ball.radius) - (brick[i].rectangle.y)) < ((ball.position.x + ball.radius) - (brick[i].rectangle.x)))ball.bounceSide.left = false;
						else ball.bounceSide.up = false;
					}
					if (ball.bounceSide.right == true)
					{
						if (((ball.position.y + ball.radius) - (brick[i].rectangle.y)) < ((brick[i].rectangle.x + brick[i].rectangle.width) - (ball.position.x - ball.radius)))ball.bounceSide.right = false;
						else ball.bounceSide.up = false;
					}
				}
				if (ball.bounceSide.right == true && ball.speed.x < 0) ball.invertX = true;
				if (ball.bounceSide.left == true && ball.speed.x > 0) ball.invertX = true;
				if (ball.bounceSide.down == true && ball.speed.y < 0) ball.invertY = true;
				if (ball.bounceSide.up == true && ball.speed.y > 0) ball.invertY = true;
				ball.bounceSide.up = false;
				ball.bounceSide.down = false;
				ball.bounceSide.left = false;
				ball.bounceSide.right = false;
			}
			if (ball.invertY == true)
			{
				ball.speed.y *= -1.0f;
				ball.invertY = false;
				break;
			}
			if (ball.invertX == true)
			{
				ball.invertX = false;
				ball.speed.x *= -1.0f;
				break;
			}
		}
		if (player.lives <= 0)
		{
			lastState = gameplay;
			gamestate = gameOver;
			scorestate = lost;
		}
		bricksRemmaining = 0;
		for (int i = 0; i < maxBrickAmmount; i++)
		{
			if (brick[i].exists == true)bricksRemmaining += 1;
		}
		if (bricksRemmaining == 0)
		{
			switch (level)
			{
			case lvl4:
				lastState = gameplay;
				gamestate = gameOver;
				scorestate = won;
				break;
			case lvl3:
				level = lvl4;
				break;
			case lvl2:
				level = lvl3;
				break;
			case lvl1:
				level = lvl2;
				break;
			}
			levelTransition();
		}
	}
	if (pause&&IsKeyPressed(KEY_DOWN))optionCounterPause--;
	if (pause&&IsKeyPressed(KEY_UP))optionCounterPause++;
	if (optionCounterPause < 1)optionCounterPause = 3;
	if (optionCounterPause > 3)optionCounterPause = 1;
	framesCounter++;
	if (pause)
	{
		if (optionCounterPause == 3)
		{
			Return.color = selectedOption;
			Options.color = notSelectedOption;
			Exit.color = notSelectedOption;
			Return.textColor = selectedText;
			Options.textColor = notSelectedText;
			Exit.textColor = notSelectedText;
			if (IsKeyPressed(KEY_ENTER))pause = !pause;
		}
		if (optionCounterPause == 2)
		{
			Return.color = notSelectedOption;
			Options.color = selectedOption;
			Exit.color = notSelectedOption;
			Return.textColor = notSelectedText;
			Options.textColor = selectedText;
			Exit.textColor = notSelectedText;
			if (IsKeyPressed(KEY_ENTER))gamestate = optionsMenu;
			lastState = gameplay;
		}
		if (optionCounterPause == 1)
		{
			Return.color = notSelectedOption;
			Options.color = notSelectedOption;
			Exit.color = selectedOption;
			Return.textColor = notSelectedText;
			Options.textColor = notSelectedText;
			Exit.textColor = selectedText;
			if (IsKeyPressed(KEY_ENTER)) {
				optionCounterPause = 3;
				gamestate = menu;
			}
		}
	}
}

void drawGameplay() 
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(player.rectangle.x, player.rectangle.y, player.rectangle.width, player.rectangle.height, GREEN);
	DrawText(TextFormat("LEVEL %i", static_cast<int>(level) + 1), levelText.x, levelText.y, levelTextFont, WHITE);
	DrawCircleV(ball.position, ball.radius, YELLOW);
	DrawText(TextFormat("Lives left: %i", player.lives), livesText.x, livesText.y, livesTextFont, WHITE);
	for (int i = 0; i < maxBrickAmmount; i++)
	{
		Color auxcolor;
		if (i % 2 == 0)	auxcolor = RED;
		else auxcolor = BLUE;
		if (brick[i].exists == true)
		{
			DrawRectangle(brick[i].rectangle.x, brick[i].rectangle.y, brick[i].rectangle.width, brick[i].rectangle.height, auxcolor);
		}
	}
	if (pause)
	{
		if (((framesCounter / 30) % 2)) DrawText("PAUSED", pausedText.x, pausedText.y, pausedTextFont, WHITE);
		DrawRectangle(Return.rectangle.x, Return.rectangle.y, Return.rectangle.width, Return.rectangle.height, Return.color);
		DrawRectangle(Options.rectangle.x, Options.rectangle.y, Options.rectangle.width, Options.rectangle.height, Options.color);
		DrawRectangle(Exit.rectangle.x, Exit.rectangle.y, Exit.rectangle.width, Exit.rectangle.height, Exit.color);
		DrawText("Return", Return.textPos.x, Return.textPos.y, Return.textFont, Return.textColor);
		DrawText("Options", Options.textPos.x, Options.textPos.y, Options.textFont, Options.textColor);
		DrawText("Exit", Exit.textPos.x, Exit.textPos.y, Exit.textFont, Exit.textColor);
	}
	EndDrawing();
}

void levelTransition() 
{
	for (int i = 0; i < maxBrickAmmount; i++)
	{
		switch (level)
		{
		case lvl1:
			if (i < lvl1BrickAmmount)
			{
				brick[i].exists = true;
			}
			else
			{
				brick[i].exists = false;
			}
			break;
		case lvl2:
			if (i < lvl2BrickAmmount)
			{
				brick[i].exists = true;
			}
			else
			{
				brick[i].exists = false;
			}
			break;
		case lvl3:
			if (i < lvl3BrickAmmount)
			{
				brick[i].exists = true;
			}
			else
			{
				brick[i].exists = false;
			}
			break;
		case lvl4:
			if (i < lvl4BrickAmmount)
			{
				brick[i].exists = true;
			}
			else
			{
				brick[i].exists = false;
			}
			break;
		}

	}
	player.rectangle.x = GetScreenWidth() / 2;
	player.ballAttached = true;
}