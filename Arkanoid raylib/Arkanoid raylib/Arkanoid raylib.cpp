#include "raylib.h"
#include <math.h>

struct Bounce {
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
};
bool invertY = false;
bool invertX = false;
Bounce bounceSide;
enum Scorestate
{
	lost,
	won,
	playing
};
Scorestate scorestate;
enum State
{
	menu,
	options,
	resetingValues,
	gameplay,
	finalScreen,
	closing
};
State gamestate = menu;
struct Player
{
	Rectangle rectangle;
	float speed;
	bool ballAttached = true;
	float centerPosition;
	int vidas;
};
float GetCenterPos(Player player);
int bricksRemmaining = 0;
int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Arkanoid raylib- Inaki Diez");//I�aki

	Player player;
	player.rectangle.width = 100;
	player.rectangle.height = 10;
	player.rectangle.x = GetScreenWidth() / 2;
	player.rectangle.y = GetScreenHeight() - player.rectangle.height * 2;
	player.speed = 5;
	player.vidas = 5;

	Vector2 ballPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
	Vector2 ballSpeed = { 0.0f, 0.0f };

	const int brickAmmount = 64;
	int brickLines = 0;
	Rectangle Brick[brickAmmount];
	bool BrickExists[brickAmmount];

	for (int i = 0; i < brickAmmount; i++)
	{
		BrickExists[i] = true;
		Brick[i].height = 30;
		Brick[i].width = 40;
		Brick[i].y = 0;
		Brick[i].x = 50 * i;
		if (Brick[i].x + Brick[i].width >= GetScreenWidth())
		{
			while (Brick[i].x + Brick[i].width >= GetScreenWidth())
			{
				Brick[i].y += 40;
				Brick[i].x -= GetScreenWidth();
			}
		}
		brickLines += Brick[i].width + 10;
	}
	brickLines = brickLines / GetScreenWidth();
	int ballRadius = 10;
	SetExitKey(NULL);
	bool pause = false;
	int framesCounter = 0;

	SetTargetFPS(60);
	struct TextDivider
	{
		float x;
		float y;
		float font;
	};
	Rectangle Jugar;
	Jugar.width = screenWidth / 3;
	Jugar.height = screenHeight / 6;
	Jugar.x = screenWidth / 2 - Jugar.width / 2;
	Jugar.y = screenHeight / 4;
	TextDivider playText;
	TextDivider optionsText;
	TextDivider exitText;
	playText.x = 2.3f;
	playText.y = 3.7f;
	playText.font = 9.0f;
	optionsText.x = 2.6f;
	optionsText.y = 2.1f;
	optionsText.font = 9.0f;
	exitText.x = 2.3f;
	exitText.y = 1.45;
	exitText.font = 9.0f;
	Rectangle Opciones;
	Opciones.width = screenWidth / 3;
	Opciones.height = screenHeight / 6;
	Opciones.x = screenWidth / 2 - Jugar.width / 2;
	Opciones.y = screenHeight / 2.2;
	Rectangle Salir;
	Salir.width = screenWidth / 3;
	Salir.height = screenHeight / 6;
	Salir.x = screenWidth / 2 - Jugar.width / 2;
	Salir.y = screenHeight / 1.5;
	int opciones = 3;
	Color selectedOption = WHITE;
	Color notSelectedOption = BLUE;
	Color selectedText = BLUE;
	Color notSelectedText = WHITE;
	while (!WindowShouldClose() && gamestate != closing)
	{
		if (gamestate == menu)
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
				if (IsKeyDown(KEY_ENTER)&&gamestate==menu) gamestate = gameplay;
			}
			EndDrawing();
		}
		if (gamestate == options)
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
				//DrawText("Play", screenWidth / playText.x, screenHeight / playText.y, screenHeight / playText.font, notSelectedText);
				DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, notSelectedOption);
				//DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, notSelectedText);
				DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, selectedOption);
				//DrawText("Salir", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, selectedText);
				if (IsKeyPressed(KEY_ENTER)) gamestate = closing;
			}
			if (opciones == 2)
			{
				DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, notSelectedOption);
				//DrawText("Play", screenWidth / playText.x, screenHeight / playText.y, screenHeight / playText.font, notSelectedText);
				DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, selectedOption);
				//DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, selectedText);
				DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, notSelectedOption);
				//DrawText("Salir", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, notSelectedText);
			}
			if (opciones == 3)
			{
				DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, selectedOption);
				//DrawText("Play", screenWidth / playText.x, screenHeight / playText.y, screenHeight / playText.font, selectedText);
				DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, notSelectedOption);
				//DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, notSelectedText);
				DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, notSelectedOption);
				//DrawText("Salir", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, notSelectedText);
				if (IsKeyPressed(KEY_ENTER)) gamestate = gameplay;
			}
			EndDrawing();
		}
		if (gamestate == gameplay)
		{
			if (IsKeyPressed(KEY_ESCAPE)) pause = !pause;
			if (pause == false)
			{
				if (IsKeyDown('T'))ballSpeed.y = -5.0f;
				if (IsKeyDown('G'))ballSpeed.y = 5.0f;
				if (IsKeyDown('F'))ballSpeed.x = -2.5f;
				if (IsKeyDown('H'))ballSpeed.x = 2.5f;

				if (player.rectangle.x + player.rectangle.width <= GetScreenWidth())
					if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))player.rectangle.x += player.speed;
				if (player.rectangle.x >= 0)
					if (IsKeyDown(KEY_LEFT) || IsKeyDown('A')) player.rectangle.x -= player.speed;
				if (player.ballAttached == true)
					if (IsKeyPressed(KEY_SPACE))
					{
						player.ballAttached = false;
						ballSpeed = { 0.0f,-5.0f };
					}
				ballPosition.x += ballSpeed.x;
				ballPosition.y += ballSpeed.y;

				if (ballPosition.y + ballRadius >= GetScreenHeight())
				{
					player.ballAttached = true;
					player.vidas--;
				}
				if (player.ballAttached == true)ballPosition = { GetCenterPos(player), player.rectangle.y - ballRadius };
				if (ballPosition.x + ballRadius >= (GetScreenWidth()) && ballSpeed.x > 0) ballSpeed.x *= -1.0f;
				if (ballPosition.x <= ballRadius && ballSpeed.x < 0) ballSpeed.x *= -1.0f;
				if ((ballPosition.y <= ballRadius) && ballSpeed.y < 0) ballSpeed.y *= -1.0f;
				if (CheckCollisionCircleRec(ballPosition, ballRadius, player.rectangle))
				{
					if (ballSpeed.y > 0)
					{
						ballSpeed.y *= -1;
						ballSpeed.x = (ballPosition.x - player.rectangle.x - player.rectangle.width / 2) / (player.rectangle.width / 2) * 4;
					}
				}
				for (int i = 0; i < brickAmmount; i++)
				{
					if (BrickExists[i] == true && CheckCollisionCircleRec(ballPosition, ballRadius, Brick[i]))
					{
						if (ballSpeed.y < 0) {
							if ((ballPosition.y - ballRadius) <= (Brick[i].y + Brick[i].height)) {
								bounceSide.down = true;
								BrickExists[i] = false;   // TENER UNO SOLO DE ESTOS EN EL IF GENERAL
							}
						}
						if (ballSpeed.y > 0)
						{
							if ((ballPosition.y + ballRadius) >= (Brick[i].y)) {
								bounceSide.up = true;
								BrickExists[i] = false;
							}
						}
						if (ballSpeed.x < 0) {
							if ((ballPosition.x - ballRadius) <= (Brick[i].x + Brick[i].width)) {
								bounceSide.right = true;
								BrickExists[i] = false;
							}
						}
						if (ballSpeed.x > 0) {
							if ((ballPosition.x + ballRadius) >= (Brick[i].x)) {
								bounceSide.left = true;
								BrickExists[i] = false;
							}
						}
						if (bounceSide.down == true && bounceSide.up == true)
						{
							if (((Brick[i].y + Brick[i].height) - (ballPosition.y - ballRadius)) < ((ballPosition.y + ballRadius) - (Brick[i].y))) bounceSide.up = false;
							else bounceSide.down = false;
						}
						if (bounceSide.left == true && bounceSide.right == true)
						{
							if (((Brick[i].x + Brick[i].width) - (ballPosition.x - ballRadius)) < ((ballPosition.x + ballRadius) - (Brick[i].x))) bounceSide.right = false;
							else bounceSide.left == false;
						}
						if (bounceSide.down == true)
						{
							if (bounceSide.left == true)
							{
								if (((Brick[i].y + Brick[i].height) - (ballPosition.y - ballRadius)) < ((ballPosition.x + ballRadius) - (Brick[i].x)))bounceSide.left = false;
								else bounceSide.down = false;

							}
							if (bounceSide.right == true)
							{
								if (((Brick[i].y + Brick[i].height) - (ballPosition.y - ballRadius)) < ((Brick[i].x + Brick[i].width) - (ballPosition.x - ballRadius)))bounceSide.right = false;
								else bounceSide.down = false;
							}
						}
						if (bounceSide.up == true)
						{
							if (bounceSide.left == true)
							{
								if (((ballPosition.y + ballRadius) - (Brick[i].y)) < ((ballPosition.x + ballRadius) - (Brick[i].x)))bounceSide.left = false;
								else bounceSide.up = false;
							}
							if (bounceSide.right == true)
							{
								if (((ballPosition.y + ballRadius) - (Brick[i].y)) < ((Brick[i].x + Brick[i].width) - (ballPosition.x - ballRadius)))bounceSide.right = false;
								else bounceSide.up = false;
							}
						}
						if (bounceSide.right == true && ballSpeed.x < 0) invertX = true;
						if (bounceSide.left == true && ballSpeed.x > 0) invertX = true;
						if (bounceSide.down == true && ballSpeed.y < 0) invertY = true;
						if (bounceSide.up == true && ballSpeed.y > 0) invertY = true;
						bounceSide.up = false;
						bounceSide.down = false;
						bounceSide.left = false;
						bounceSide.right = false;
					}
					if (invertY == true)
					{
						ballSpeed.y *= -1.0f;
						invertY = false;
						break;
					}
					if (invertX == true)
					{
						invertX = false;
						ballSpeed.x *= -1.0f;
						break;
					}
				}
				if (player.vidas <= 0)
				{
					gamestate = finalScreen;
					scorestate = lost;
				}
				bricksRemmaining = 0;
				for (int i = 0; i < brickAmmount; i++)
				{
					if (BrickExists[i] == true)bricksRemmaining += 1;
				}
				if (bricksRemmaining == 0)
				{
					gamestate = finalScreen;
					scorestate = won;
				}
			}
			if (pause&&IsKeyPressed(KEY_DOWN))opciones--;
			if (pause&&IsKeyPressed(KEY_UP))opciones++;
			if (opciones < 1)opciones = 3;
			if (opciones > 3)opciones = 1;
			framesCounter++;
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText(TextFormat("Lives left: %i", player.vidas), 40, GetScreenHeight() - 40, 20, GRAY);
			for (int i = 0; i < brickAmmount; i++)
			{
				Color auxcolor;
				if (i % 2 == 0)	auxcolor = RED;
				else auxcolor = BLUE;
				if (BrickExists[i] == true)
				{
					DrawRectangle(Brick[i].x, Brick[i].y, Brick[i].width, Brick[i].height, auxcolor);
				}
			}
			DrawCircleV(ballPosition, ballRadius, YELLOW);
			DrawRectangle(player.rectangle.x, player.rectangle.y, player.rectangle.width, player.rectangle.height, GREEN);
			if (pause)
			{
				if (((framesCounter / 30) % 2)) DrawText("PAUSED", 350, screenHeight / 8, 30, GRAY);
				if (opciones == 3)
				{
					DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, selectedOption);
					DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, notSelectedOption);
					DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, notSelectedOption);
					DrawText("Return", screenWidth / optionsText.x, screenHeight / playText.y, screenHeight / playText.font, selectedText);
					DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, notSelectedText);
					DrawText("Menu", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, notSelectedText);
					if(IsKeyPressed(KEY_ENTER))pause = !pause;
				}
				if (opciones == 2)
				{
					DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, notSelectedOption);
					DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, selectedOption);
					DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, notSelectedOption);
					DrawText("Return", screenWidth / optionsText.x, screenHeight / playText.y, screenHeight / playText.font, notSelectedText);
					DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, selectedText);
					DrawText("Menu", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, notSelectedText);
				}
				if (opciones == 1)
				{
					DrawRectangle(Jugar.x, Jugar.y, Jugar.width, Jugar.height, notSelectedOption);
					DrawRectangle(Opciones.x, Opciones.y, Opciones.width, Opciones.height, notSelectedOption);
					DrawRectangle(Salir.x, Salir.y, Salir.width, Salir.height, selectedOption);
					DrawText("Return", screenWidth / optionsText.x, screenHeight / playText.y, screenHeight / playText.font, notSelectedText);
					DrawText("Options", screenWidth / optionsText.x, screenHeight / optionsText.y, screenHeight / optionsText.font, notSelectedText);
					DrawText("Menu", screenWidth / exitText.x, screenHeight / exitText.y, screenHeight / exitText.font, selectedText);
					if (IsKeyPressed(KEY_ENTER))gamestate = menu;
				}
			}
			EndDrawing();
		}
		if (gamestate == finalScreen)
		{
			if (IsKeyDown('R'))gamestate = resetingValues;
			BeginDrawing();
			ClearBackground(BLUE);
			if (scorestate == lost)
			{
				DrawText("Perdiste :(", screenWidth / 3, screenHeight / 3, 50, WHITE);
			}
			if (scorestate == won)
			{
				DrawText("Ganaste :)", screenWidth / 3, screenHeight / 3, 50, WHITE);
			}
			DrawText("Presiona 'R' para jugar de nuevo B)", screenWidth / 6, screenHeight / 2, 30, WHITE);
			EndDrawing();
		}
		if (gamestate == resetingValues)
		{
			for (int i = 0; i < brickAmmount; i++)
			{
				BrickExists[i] = true;
			}
			player.rectangle.x = GetScreenWidth() / 2;
			player.vidas = 5;
			player.ballAttached = true;
			ballPosition = { GetCenterPos(player), player.rectangle.y - ballRadius };
			gamestate = gameplay;
		}
	}
	CloseWindow();
	return 0;
}
float GetCenterPos(Player player)
{
	return player.centerPosition = player.rectangle.x + player.rectangle.width / 2;
}
