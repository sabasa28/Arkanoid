#include "gameplay.h"

#include "raylib.h"

#include "game_elements/ball.h"
#include "game_elements/bricks.h"
#include "game_elements/player.h"
#include "game_elements/powerUP.h"
#include "general_elements/console.h"
#include "general_elements/codingTools.h"
#include "states/game.h"
#include "assets/images.h"
#include "assets/sound.h"

namespace arkanoid_IDG {
	static Button Return;
	static Button optionsbutton;
	static Button exitbutton;
	Vector2 pausedText;
	Vector2 pausedTextDiv{ 2.4f,8.0f };
	static int pausedTextFont;
	static float pausedTextFontDiv = 15.0f;
	Vector2 levelText;
	Vector2 levelTextDiv{ 2.5f,1.5f };
	static int levelTextFont;
	static float levelTextFontDiv = 10.0f;
	Vector2 livesText;
	Vector2 livesTextDiv{ 20.0f,1.1f };
	static int livesTextFont;
	static float livesTextFontDiv = 22.5f;
	bool pause = false;
	static int optionCounterPause = 3;
	static bool ActiveBarrier = false;
	lvl level = lvl1;
	bool speedsDecreased=false;
	bool ballShouldCollideBrick(Brick brick, Ball ball);
	void applySpeedToBall(Ball &ball, Player player);
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
		Return.textFont = static_cast<int>(screenHeight / Return.textFontDivider);
		Return.textPos.x = screenWidth / Return.textDivider.x;
		Return.textPos.y = screenHeight / Return.textDivider.y;
		optionsbutton.divider.y = 2.2f;
		optionsbutton.textFontDivider = 9.0f;
		optionsbutton.textDivider.x = 2.6f;
		optionsbutton.textDivider.y = 2.1f;
		optionsbutton.rectangle.width = Return.rectangle.width;
		optionsbutton.rectangle.height = Return.rectangle.height;
		optionsbutton.rectangle.x = Return.rectangle.x;
		optionsbutton.rectangle.y = screenHeight / optionsbutton.divider.y;
		optionsbutton.textFont = static_cast<int>(screenHeight / optionsbutton.textFontDivider);
		optionsbutton.textPos.x = screenWidth / optionsbutton.textDivider.x;
		optionsbutton.textPos.y = screenHeight / optionsbutton.textDivider.y;
		exitbutton.divider.y = 1.5f;
		exitbutton.textFontDivider = 9.0f;
		exitbutton.textDivider.x = 2.3f;
		exitbutton.textDivider.y = 1.45f;
		exitbutton.rectangle.width = Return.rectangle.width;
		exitbutton.rectangle.height = Return.rectangle.height;
		exitbutton.rectangle.x = Return.rectangle.x;
		exitbutton.rectangle.y = screenHeight / exitbutton.divider.y;
		exitbutton.textFont = static_cast<int>(screenHeight / exitbutton.textFontDivider);
		exitbutton.textPos.x = screenWidth / exitbutton.textDivider.x;
		exitbutton.textPos.y = screenHeight / exitbutton.textDivider.y;
		pausedText.x = screenWidth / pausedTextDiv.x;
		pausedText.y = screenHeight / pausedTextDiv.y;
		pausedTextFont = static_cast<int>(screenHeight / pausedTextFontDiv);
		livesText.x = screenWidth / livesTextDiv.x;
		livesText.y = screenHeight / livesTextDiv.y;
		livesTextFont = static_cast<int>(screenHeight / livesTextFontDiv);
		levelText.x = screenWidth / levelTextDiv.x;
		levelText.y = screenHeight / levelTextDiv.y;
		levelTextFont = static_cast<int>(screenHeight / levelTextFontDiv);
	}

	void updateGameplay() {

		if (IsKeyPressed(KEY_ESCAPE))
		{
			optionCounterPause = 3;
			pause = !pause;
		}

		if (pause == false)
		{
			UpdateMusicStream(originalMusic1);

			if (player.rectangle.x + player.rectangle.width < screenWidth)
			{
				if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))
				{
					player.rectangle.x += player.speed*GetFrameTime() * 70;
				}
			}
			if (player.rectangle.x > 0)
			{
				if (IsKeyDown(KEY_LEFT) || IsKeyDown('A'))
				{
					player.rectangle.x -= player.speed*GetFrameTime() * 70;
				}
			}

			if (player.ballAttached == true && IsKeyPressed(KEY_SPACE))
			{
				player.ballAttached = false;
				ball.speed = { ball.launchSpeed.x, ball.launchSpeed.y };
			}

			ball.position.x += ball.speed.x*GetFrameTime() * 70;
			ball.position.y += ball.speed.y*GetFrameTime() * 70;

			if (ball.position.y + ball.radius >= GetScreenHeight())
			{
				if (ActiveBarrier == true)
				{
					ball.speed.y *= -1;
					ActiveBarrier = false;
				}
				else
				{
					player.ballAttached = true;
					ball.sizeState = normalSize;
					ball.radius = (screenWidth + screenHeight) / ball.radiusDivider;
					player.lives--;
				}
			}

			if (player.ballAttached == true)
			{
				ball.position = { GetCenterXPos(player), player.rectangle.y - ball.radius };
			}

			if (ballIsOffScreenLimits(ball)) ball.speed.x *= -1.0f;

			if ((ball.position.y <= ball.radius) && ball.speed.y < 0) ball.speed.y *= -1.0f;

			if (CheckCollisionCircleRec(ball.position, ball.radius, player.rectangle))
			{
				if (ball.speed.y > 0)
				{
					if (speedsDecreased == true)
					{
						resetSpeeds();
						speedsDecreased = false;
					}
					ball.speed.y = ball.generalYSpeed;
					applySpeedToBall(ball, player);
					PlaySound(originalSound);
				}
			}

			for (int i = 0; i < maxBrickAmmount; i++)
			{
				if (ballShouldCollideBrick(brick[i],ball))
				{
					brick[i].collidedLastFrame = true;

					if (brick[i].lives>1)
					{
						brick[i].lives--;
						brick[i].color = WHITE;
					}
					else
					{
						brick[i].exists = false;
					}

					if (ball.speed.y < 0) 
					{
						ball.generalDir.up = true;
					}
					if (ball.speed.y > 0)
					{
						ball.generalDir.down = true;
					}
					if (ball.speed.x < 0) 
					{
						ball.generalDir.left = true;
					}
					if (ball.speed.x > 0) 
					{
						ball.generalDir.right = true;
					}

					if (ball.generalDir.up == true)
					{
						if (ball.generalDir.right == true)
						{
							if ((brickBottomSideY(brick[i]) - ballTopSideY(ball)) < (ballRightSideX(ball) - brickLeftSideX(brick[i])))ball.generalDir.right = false;
							else ball.generalDir.up = false;
						}
						if (ball.generalDir.left == true)
						{
							if ((brickBottomSideY(brick[i]) - ballTopSideY(ball)) < (brickRightSideX(brick[i]) - ballLeftSideX(ball)))ball.generalDir.left = false;
							else ball.generalDir.up = false;
						}
					}

					if (ball.generalDir.down == true)
					{
						if (ball.generalDir.right == true)
						{
							if ((ballBottomSideY(ball) - brickTopSideY(brick[i])) < (ballRightSideX(ball) - brickLeftSideX(brick[i])))ball.generalDir.right = false;
							else ball.generalDir.down = false;
						}
						if (ball.generalDir.left == true)
						{
							if ((ballBottomSideY(ball) - brickTopSideY(brick[i])) < (brickRightSideX(brick[i]) - ballLeftSideX(ball)))ball.generalDir.left = false;
							else ball.generalDir.down = false;
						}
					}

					if (ball.generalDir.left == true || ball.generalDir.right == true)
					{
						ball.invertX = true;
					}
					if (ball.generalDir.up == true || ball.generalDir.down == true)
					{
						ball.invertY = true;
					}
				
					ball.generalDir.down = false;
					ball.generalDir.up = false;
					ball.generalDir.right = false;
					ball.generalDir.left = false;

					switch (brick[i].content)
					{
					case tpPlayer:
						playerToRandomX();
						break;
					case shrinkBall:
						divideBallRadius();
						break;
					case enlargeBall:
						multiplyBallRadius();
						break;
					case barrier:
						ActiveBarrier = true;
						break;
					case slowMo:
						divideSpeeds(speedsDecreased);
						speedsDecreased = true;
						break;
					default:
						break;
					}
				}
				else 
				{
					brick[i].collidedLastFrame = false;
				}

				if (ball.invertY == true)
				{
					ball.speed.y *= -1.0f;
					ball.invertY = false;
					break;
				}
				if (ball.invertX == true)
				{
					ball.speed.x *= -1.0f;
					ball.invertX = false;
					break;
				}
			}

			if (player.lives <= 0)
			{
				lastState = gameplay;
				gamestate = gameOver;
				scorestate = lost;
			}

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
			bricksRemmaining = 0;
		}
		
		if (pause)
		{
			if (IsKeyPressed(KEY_DOWN))
			{
				optionCounterPause--;
			}
			if (IsKeyPressed(KEY_UP))
			{
				optionCounterPause++;
			}

			if (optionCounterPause < 1)
			{
				optionCounterPause = 3;
			}
			if (optionCounterPause > 3)
			{
				optionCounterPause = 1;
			}

			if (optionCounterPause == 3)
			{
				Return.color = selectedOption;
				optionsbutton.color = notSelectedOption;
				exitbutton.color = notSelectedOption;
				Return.textColor = selectedText;
				optionsbutton.textColor = notSelectedText;
				exitbutton.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER))pause = !pause;
			}

			if (optionCounterPause == 2)
			{
				Return.color = notSelectedOption;
				optionsbutton.color = selectedOption;
				exitbutton.color = notSelectedOption;
				Return.textColor = notSelectedText;
				optionsbutton.textColor = selectedText;
				exitbutton.textColor = notSelectedText;
				if (IsKeyPressed(KEY_ENTER))gamestate = optionsMenu;
				lastState = gameplay;
			}

			if (optionCounterPause == 1)
			{
				Return.color = notSelectedOption;
				optionsbutton.color = notSelectedOption;
				exitbutton.color = selectedOption;
				Return.textColor = notSelectedText;
				optionsbutton.textColor = notSelectedText;
				exitbutton.textColor = selectedText;
				if (IsKeyPressed(KEY_ENTER)) {
					optionCounterPause = 3;
					gamestate = menu;
					resetSounds();
				}
			}
		}
	}

	void drawGameplay()
	{
		BeginDrawing();
		DrawTexture(background, 0, 0, WHITE);
		DrawRectangle(static_cast<int>(player.rectangle.x), static_cast<int>(player.rectangle.y), static_cast<int>(player.rectangle.width), static_cast<int>(player.rectangle.height), BLUE);
		DrawText(TextFormat("LEVEL %i", static_cast<int>(level) + 1), static_cast<int>(levelText.x), static_cast<int>(levelText.y), levelTextFont, WHITE);
		DrawCircleV(ball.position, ball.radius, YELLOW);
		DrawText(TextFormat("Lives left: %i", player.lives), static_cast<int>(livesText.x), static_cast<int>(livesText.y), livesTextFont, WHITE);
		if (ActiveBarrier==true)
		{
			DrawRectangle(static_cast<int>(barrierRec.x), static_cast<int>(barrierRec.y), static_cast<int>(barrierRec.width), static_cast<int>(barrierRec.height), YELLOW);
		}
		for (int i = 0; i < maxBrickAmmount; i++)
		{
			if (brick[i].exists == true)
			{
				DrawRectangle(static_cast<int>(brick[i].rectangle.x), static_cast<int>(brick[i].rectangle.y), static_cast<int>(brick[i].rectangle.width), static_cast<int>(brick[i].rectangle.height), brick[i].color);
			}
		}
		if (pause)
		{
			DrawText("PAUSED", static_cast<int>(pausedText.x), static_cast<int>(pausedText.y), pausedTextFont, WHITE);
			DrawRectangle(static_cast<int>(Return.rectangle.x), static_cast<int>(Return.rectangle.y), static_cast<int>(Return.rectangle.width), static_cast<int>(Return.rectangle.height), Return.color);
			DrawRectangle(static_cast<int>(optionsbutton.rectangle.x), static_cast<int>(optionsbutton.rectangle.y), static_cast<int>(optionsbutton.rectangle.width), static_cast<int>(optionsbutton.rectangle.height), optionsbutton.color);
			DrawRectangle(static_cast<int>(exitbutton.rectangle.x), static_cast<int>(exitbutton.rectangle.y), static_cast<int>(exitbutton.rectangle.width), static_cast<int>(exitbutton.rectangle.height), exitbutton.color);
			DrawText("Return", static_cast<int>(Return.textPos.x), static_cast<int>(Return.textPos.y), Return.textFont, Return.textColor);
			DrawText("Options", static_cast<int>(optionsbutton.textPos.x), static_cast<int>(optionsbutton.textPos.y), optionsbutton.textFont, optionsbutton.textColor);
			DrawText("Exit", static_cast<int>(exitbutton.textPos.x), static_cast<int>(exitbutton.textPos.y), exitbutton.textFont, exitbutton.textColor);
		}
		EndDrawing();
	}

	

	bool ballShouldCollideBrick(Brick brick, Ball ball)
	{
		if (brick.exists == true && brick.collidedLastFrame == false && CheckCollisionCircleRec(ball.position, ball.radius, brick.rectangle))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void applySpeedToBall(Ball &ball, Player player)
	{
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces))
		{
			ball.speed.x = -ball.speedX6;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 2) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 1)))
		{
			ball.speed.x = -ball.speedX5;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 3) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 2)))
		{
			ball.speed.x = -ball.speedX4;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 4) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 3)))
		{
			ball.speed.x = -ball.speedX3;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 5) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 4)))
		{
			ball.speed.x = -ball.speedX2;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 6) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 5)))
		{
			ball.speed.x = -ball.speedX1;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 7) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 6)))
		{
			ball.speed.x = ball.speedX1;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 8) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 7)))
		{
			ball.speed.x = ball.speedX2;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 9) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 8)))
		{
			ball.speed.x = ball.speedX3;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 10) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 9)))
		{
			ball.speed.x = ball.speedX4;
		}
		if (ball.position.x < player.rectangle.x + (player.rectangle.width / player.pieces * 11) && (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 10)))
		{
			ball.speed.x = ball.speedX5;
		}
		if (ball.position.x >= player.rectangle.x + (player.rectangle.width / player.pieces * 11))
		{
			ball.speed.x = ball.speedX6;
		}
	}

	void levelTransition()
	{
		initBricks();
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
		player.rectangle.x = static_cast<float>(GetScreenWidth() / 2);
		player.ballAttached = true;
		ActiveBarrier = false;
		ball.radius = ball.originalRadius;
		ball.sizeState = normalSize;
	}
}