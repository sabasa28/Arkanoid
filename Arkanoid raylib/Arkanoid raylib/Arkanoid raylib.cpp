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
					ballSpeed = { 0.0f,-5.0f };
				}
			ballPosition.x += ballSpeed.x;
			ballPosition.y += ballSpeed.y;
			
			if (player.ballAttached == true)ballPosition = Vector2 { GetCenterPos(player), player.rectangle.y-ballRadius };
			if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
			if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
			
			if (CheckCollisionCircleRec(ballPosition, ballRadius,player.rectangle))
			{
				if (ballSpeed.y > 0)
				{
					ballSpeed.y *= -1;
					ballSpeed.x = (ballPosition.x - player.rectangle.x-player.rectangle.width/2) / (player.rectangle.width/2) * 5;
				}
			}
			
			for (int i = 0; i < brickAmmount; i++)
			{
				if (BrickExists[i]==true)
				{
					if (((ballPosition.y - ballRadius) <= (Brick[i].y + Brick[i].height / 2)) &&
						((ballPosition.y - ballRadius) > (Brick[i].y + Brick[i].height / 2 + ballSpeed.y)) &&
						((fabs(ballPosition.x - Brick[i].x)) < (Brick[i].width / 2 + ballRadius * 2 / 3)) && (ballSpeed.y < 0))
					{
						BrickExists[i] = false;
						ballSpeed.y *= -1;
					}
					else if (((ballPosition.y + ballRadius) >= (Brick[i].y - Brick[i].height / 2)) &&
						((ballPosition.y + ballRadius) < (Brick[i].y - Brick[i].height / 2 + ballSpeed.y)) &&
						((fabs(ballPosition.x - Brick[i].x)) < (Brick[i].width / 2 + ballRadius * 2 / 3)) && (ballSpeed.y > 0))
					{
						BrickExists[i] = false;
						ballSpeed.y *= -1;
					}
					else if (((ballPosition.x + ballRadius) >= (Brick[i].x - Brick[i].width / 2)) &&
						((ballPosition.x + ballRadius) < (Brick[i].x - Brick[i].width / 2 + ballSpeed.x)) &&
						((fabs(ballPosition.y - Brick[i].y)) < (Brick[i].height / 2 + ballRadius * 2 / 3)) && (ballSpeed.x > 0))
					{
						BrickExists[i] = false;
						ballSpeed.x *= -1;
					}
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

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
float GetCenterPos(Player player)
{
	return player.centerPosition = player.rectangle.x + player.rectangle.width / 2;
}
