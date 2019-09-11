#include "raylib.h"
#include <math.h>
struct Player
{
	Rectangle rectangle;		
	float speed;
	bool ballAttached = true;
	float centerPosition;
};
float GetCenterPos(Player player);

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Arkanoid raylib");

	Player player;
	player.rectangle.width = 100;
	player.rectangle.height = 10;
	player.rectangle.x = GetScreenWidth() / 2;
	player.rectangle.y = GetScreenHeight() - player.rectangle.height*2;
	player.speed = 5;
	
	Vector2 ballPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
	Vector2 ballSpeed = { 0.0f, 0.0f };

	const int brickAmmount = 112;
	int brickLines=0;
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
		brickLines+= Brick[i].width + 10;
	}
	brickLines = brickLines/GetScreenWidth();
	int ballRadius = 10;

	bool pause = 0;
	int framesCounter = 0;

	SetTargetFPS(60);

	while (!WindowShouldClose())    
	{
		// Update

		if (IsKeyPressed(KEY_ENTER)||IsKeyPressed('P')) pause = !pause;
		if (!pause)
		{
			if(player.rectangle.x+player.rectangle.width <= GetScreenWidth())
				if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))player.rectangle.x += player.speed;
			if (player.rectangle.x >= 0)
				if (IsKeyDown(KEY_LEFT)||IsKeyDown('A')) player.rectangle.x-=player.speed;
			if (player.ballAttached == true)
				if (IsKeyPressed(KEY_SPACE))
				{
					player.ballAttached = false;
					ballSpeed = { 0.0f,-6.0f };
				}
			ballPosition.x += ballSpeed.x;
			ballPosition.y += ballSpeed.y;
			
			//check
			if (player.ballAttached == true)ballPosition = Vector2 { GetCenterPos(player), player.rectangle.y-ballRadius };
			if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
			if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
			
			if (CheckCollisionCircleRec(ballPosition, ballRadius,player.rectangle))
			{
				if (ballSpeed.y > 0)
				{
					ballSpeed.y *= -1;
					ballSpeed.x = (ballPosition.x - player.rectangle.x) / (GetCenterPos(player)) * 6;
				}
			}
			
			for (int i = 0; i < brickLines; i++)
			{
				if (BrickExists[i]==true)
				{
					// Hit below
					if (((ballPosition.y - ballRadius) <= (Brick[i].y + Brick[i].height / 2)) &&
						((ballPosition.y - ballRadius) > (Brick[i].y + Brick[i].height / 2 + ballSpeed.y)) &&
						((fabs(ballPosition.x - Brick[i].x)) < (Brick[i].width / 2 + ballRadius * 2 / 3)) && (ballSpeed.y < 0))
					{
						BrickExists[i] = false;
						ballSpeed.y *= -1;
					}
					// Hit above
					else if (((ballPosition.y + ballRadius) >= (Brick[i].y - Brick[i].height / 2)) &&
						((ballPosition.y + ballRadius) < (Brick[i].y - Brick[i].height / 2 + ballSpeed.y)) &&
						((fabs(ballPosition.x - Brick[i].x)) < (Brick[i].width / 2 + ballRadius * 2 / 3)) && (ballSpeed.y > 0))
					{
						BrickExists[i] = false;
						ballSpeed.y *= -1;
					}
					// Hit left
					else if (((ballPosition.x + ballRadius) >= (Brick[i].x - Brick[i].width / 2)) &&
						((ballPosition.x + ballRadius) < (Brick[i].x - Brick[i].width / 2 + ballSpeed.x)) &&
						((fabs(ballPosition.y - Brick[i].y)) < (Brick[i].height / 2 + ballRadius * 2 / 3)) && (ballSpeed.x > 0))
					{
						BrickExists[i] = false;
						ballSpeed.x *= -1;
					}
					// Hit right
					else if (((ballPosition.x - ballRadius) <= (Brick[i].x + Brick[i].width / 2)) &&
						((ballPosition.x - ballRadius) > (Brick[i].x + Brick[i].width / 2 + ballSpeed.x)) &&
						((fabs(ballPosition.y - Brick[i].y)) < (Brick[i].height / 2 + ballRadius * 2 / 3)) && (ballSpeed.x < 0))
					{
						BrickExists[i] = false;
						ballSpeed.x *= -1;
					}
				}
			}
		}
		else framesCounter++;


		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		for (int i = 0; i < brickAmmount; i++)
		{
			Color auxcolor;
			if (i%2==0)	auxcolor = RED;
			else auxcolor = BLUE;
			if (BrickExists[i]==true)
			{
				DrawRectangle(Brick[i].x, Brick[i].y, Brick[i].width, Brick[i].height, auxcolor);
			}
		}
		DrawCircleV(ballPosition, ballRadius, MAROON);
		DrawRectangle(player.rectangle.x, player.rectangle.y, player.rectangle.width, player.rectangle.height, BROWN);

		if (pause && ((framesCounter / 30) % 2)) DrawText("PAUSED", 350, 200, 30, GRAY);
		//DrawText(TextFormat("filas: %i", brickLines), 10, 10, 20, BLACK);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
float GetCenterPos(Player player)
{
	return player.centerPosition = player.rectangle.x + player.rectangle.width / 2;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define PLAYER_MAX_LIFE         5
#define LINES_OF_BRICKS         5
#define BRICKS_PER_LINE        20

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Player {
	Vector2 position;
	Vector2 size;
	int life;
} Player;

typedef struct Ball {
	Vector2 position;
	Vector2 speed;
	int radius;
	bool active;
} Ball;

typedef struct Brick {
	Vector2 position;
	bool active;
} Brick;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;

static Player player = { 0 };
static Ball ball = { 0 };
static Brick brick[LINES_OF_BRICKS][BRICKS_PER_LINE] = { 0 };
static Vector2 brickSize = { 0 };

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization (Note windowTitle is unused on Android)
	//---------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "sample game: arkanoid");

	InitGame();

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update and Draw
		//----------------------------------------------------------------------------------
		UpdateDrawFrame();
		//----------------------------------------------------------------------------------
	}
#endif
	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadGame();         // Unload loaded data (textures, sounds, models...)

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
	brickSize = (Vector2) { GetScreenWidth() / BRICKS_PER_LINE, 40 };

	// Initialize player
	player.position = (Vector2) { screenWidth / 2, screenHeight * 7 / 8 };
	player.size = (Vector2) { screenWidth / 10, 20 };
	player.life = PLAYER_MAX_LIFE;

	// Initialize ball
	ball.position = (Vector2) { screenWidth / 2, screenHeight * 7 / 8 - 30 };
	ball.speed = (Vector2) { 0, 0 };
	ball.radius = 7;
	ball.active = false;

	// Initialize bricks
	int initialDownPosition = 50;

	for (int i = 0; i < LINES_OF_BRICKS; i++)
	{
		for (int j = 0; j < BRICKS_PER_LINE; j++)
		{
			brick[i][j].position = (Vector2) { j*brickSize.x + brickSize.x / 2, i*brickSize.y + initialDownPosition };
			brick[i][j].active = true;
		}
	}
}

// Update game (one frame)
void UpdateGame(void)
{
	if (!gameOver)
	{
		if (IsKeyPressed('P')) pause = !pause;

		if (!pause)
		{
			// Player movement logic
			if (IsKeyDown(KEY_LEFT)) player.position.x -= 5;
			if ((player.position.x - player.size.x / 2) <= 0) player.position.x = player.size.x / 2;
			if (IsKeyDown(KEY_RIGHT)) player.position.x += 5;
			if ((player.position.x + player.size.x / 2) >= screenWidth) player.position.x = screenWidth - player.size.x / 2;

			// Ball launching logic
			if (!ball.active)
			{
				if (IsKeyPressed(KEY_SPACE))
				{
					ball.active = true;
					ball.speed = (Vector2) { 0, -5 };
				}
			}

			// Ball movement logic
			if (ball.active)
			{
				ball.position.x += ball.speed.x;
				ball.position.y += ball.speed.y;
			}
			else
			{
				ball.position = (Vector2) { player.position.x, screenHeight * 7 / 8 - 30 };
			}

			// Collision logic: ball vs walls 
			if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0)) ball.speed.x *= -1;
			if ((ball.position.y - ball.radius) <= 0) ball.speed.y *= -1;
			if ((ball.position.y + ball.radius) >= screenHeight)
			{
				ball.speed = (Vector2) { 0, 0 };
				ball.active = false;

				player.life--;
			}

			// Collision logic: ball vs player
			if (CheckCollisionCircleRec(ball.position, ball.radius,
				(Rectangle) {
				player.position.x - player.size.x / 2, player.position.y - player.size.y / 2, player.size.x, player.size.y
			}))
			{
				if (ball.speed.y > 0)
				{
					ball.speed.y *= -1;
					ball.speed.x = (ball.position.x - player.position.x) / (player.size.x / 2) * 5;
				}
			}

				// Collision logic: ball vs bricks
				for (int i = 0; i < LINES_OF_BRICKS; i++)
				{
					for (int j = 0; j < BRICKS_PER_LINE; j++)
					{
						if (brick[i][j].active)
						{
							// Hit below
							if (((ball.position.y - ball.radius) <= (brick[i][j].position.y + brickSize.y / 2)) &&
								((ball.position.y - ball.radius) > (brick[i][j].position.y + brickSize.y / 2 + ball.speed.y)) &&
								((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y < 0))
							{
								brick[i][j].active = false;
								ball.speed.y *= -1;
							}
							// Hit above
							else if (((ball.position.y + ball.radius) >= (brick[i][j].position.y - brickSize.y / 2)) &&
								((ball.position.y + ball.radius) < (brick[i][j].position.y - brickSize.y / 2 + ball.speed.y)) &&
								((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y > 0))
							{
								brick[i][j].active = false;
								ball.speed.y *= -1;
							}
							// Hit left
							else if (((ball.position.x + ball.radius) >= (brick[i][j].position.x - brickSize.x / 2)) &&
								((ball.position.x + ball.radius) < (brick[i][j].position.x - brickSize.x / 2 + ball.speed.x)) &&
								((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x > 0))
							{
								brick[i][j].active = false;
								ball.speed.x *= -1;
							}
							// Hit right
							else if (((ball.position.x - ball.radius) <= (brick[i][j].position.x + brickSize.x / 2)) &&
								((ball.position.x - ball.radius) > (brick[i][j].position.x + brickSize.x / 2 + ball.speed.x)) &&
								((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x < 0))
							{
								brick[i][j].active = false;
								ball.speed.x *= -1;
							}
						}
					}
				}

				// Game over logic
				if (player.life <= 0) gameOver = true;
				else
				{
					gameOver = true;

					for (int i = 0; i < LINES_OF_BRICKS; i++)
					{
						for (int j = 0; j < BRICKS_PER_LINE; j++)
						{
							if (brick[i][j].active) gameOver = false;
						}
					}
				}
		}
	}
	else
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			InitGame();
			gameOver = false;
		}
	}
}

// Draw game (one frame)
void DrawGame(void)
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	if (!gameOver)
	{
		// Draw player bar
		DrawRectangle(player.position.x - player.size.x / 2, player.position.y - player.size.y / 2, player.size.x, player.size.y, BLACK);

		// Draw player lives
		for (int i = 0; i < player.life; i++) DrawRectangle(20 + 40 * i, screenHeight - 30, 35, 10, LIGHTGRAY);

		// Draw ball
		DrawCircleV(ball.position, ball.radius, MAROON);

		// Draw bricks
		for (int i = 0; i < LINES_OF_BRICKS; i++)
		{
			for (int j = 0; j < BRICKS_PER_LINE; j++)
			{
				if (brick[i][j].active)
				{
					if ((i + j) % 2 == 0) DrawRectangle(brick[i][j].position.x - brickSize.x / 2, brick[i][j].position.y - brickSize.y / 2, brickSize.x, brickSize.y, GRAY);
					else DrawRectangle(brick[i][j].position.x - brickSize.x / 2, brick[i][j].position.y - brickSize.y / 2, brickSize.x, brickSize.y, DARKGRAY);
				}
			}
		}

		if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
	}
	else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

	EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
	// TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
	UpdateGame();
	DrawGame();
}*/