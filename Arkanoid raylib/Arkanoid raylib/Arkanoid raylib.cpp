#include "raylib.h"
#include <math.h>

struct Bounce {
	bool right= false;
	bool left= false;
	bool up= false;
	bool down= false;
};
bool invertY = false;
bool invertX = false;
Bounce bounceSide;
enum State
{
	Menu,
	Gameplay,
	FinalScreen,
	Closing
};
State Gamestate = Gameplay;
struct Player
{
	Rectangle rectangle;		
	float speed;
	bool ballAttached = true;
	float centerPosition;
	int vidas;
};
float GetCenterPos(Player player);

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Arkanoid raylib- Inaki Diez");//Iñaki

	Player player;
	player.rectangle.width = 100;
	player.rectangle.height = 10;
	player.rectangle.x = GetScreenWidth() / 2;
	player.rectangle.y = GetScreenHeight() - player.rectangle.height*2;
	player.speed = 5;
	player.vidas = 5;
	
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
			if (IsKeyDown('T'))ballSpeed.y=-5.0f;
			if (IsKeyDown('G'))ballSpeed.y=5.0f;
			if (IsKeyDown('F'))ballSpeed.x=-2.5f;
			if (IsKeyDown('H'))ballSpeed.x=2.5f;

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
			ballPosition.x += ballSpeed.x/1.5f;
			ballPosition.y += ballSpeed.y;
			
			if (ballPosition.y+ballRadius>=GetScreenHeight())
			{
				player.ballAttached = true;
				player.vidas--;
			}
			if (player.ballAttached == true)ballPosition = { GetCenterPos(player), player.rectangle.y-ballRadius };
			if (ballPosition.x + ballRadius >= (GetScreenWidth())&&ballSpeed.x>0) ballSpeed.x *= -1.0f;
			if (ballPosition.x <= ballRadius&&ballSpeed.x<0) ballSpeed.x *= -1.0f;
			if ((ballPosition.y <= ballRadius)&&ballSpeed.y<0) ballSpeed.y *= -1.0f;
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
				if (BrickExists[i] == true && CheckCollisionCircleRec(ballPosition, ballRadius, Brick[i]))
				{
					if (ballSpeed.y < 0) {
						if ((ballPosition.y - ballRadius) <= (Brick[i].y + Brick[i].height)) {
							//ballSpeed.y *= -1;
							bounceSide.down = true;
							BrickExists[i] = false;
						}
					}
					if (ballSpeed.y > 0)
					{
						if ((ballPosition.y + ballRadius) >= (Brick[i].y)) {
							//ballSpeed.y *= -1;
							bounceSide.up = true;
							BrickExists[i] = false;
						}
					}
					if (ballSpeed.x < 0) {
						if ((ballPosition.x - ballRadius) <= (Brick[i].x + Brick[i].width)) {
							//ballSpeed.x *= -1;
							bounceSide.right = true;
							BrickExists[i] = false;
						}
					}
					if (ballSpeed.x > 0) {
						if ((ballPosition.x + ballRadius) >= (Brick[i].x)) {
							//ballSpeed.x *= -1;
							bounceSide.left = true;
							BrickExists[i] = false;
						}
					}

					
					//if (bounceSide.left==true && bounceSide.right==true)
					//{
					//
					//}
					
					if (bounceSide.down==true && bounceSide.up==true)
					{
						if (((Brick[i].y + Brick[i].height)-(ballPosition.y - ballRadius))< ((ballPosition.y + ballRadius)-(Brick[i].y))) bounceSide.up=false;
						else bounceSide.down=false;
					}
					if (bounceSide.left == true && bounceSide.right == true)
					{
						if (((Brick[i].x + Brick[i].width) - (ballPosition.x - ballRadius)) < ((ballPosition.x + ballRadius) - (Brick[i].x))) bounceSide.right = false;
						else bounceSide.left == false;
					}
					if (bounceSide.down==true)
					{
						if (bounceSide.left==true)
						{
							if (((Brick[i].y + Brick[i].height) - (ballPosition.y - ballRadius)) < ((ballPosition.x + ballRadius) - (Brick[i].x)))bounceSide.left = false;
							else bounceSide.down = false;
							
						}
						if (bounceSide.right==true)
						{
							if (((Brick[i].y + Brick[i].height) - (ballPosition.y - ballRadius)) < ((Brick[i].x + Brick[i].width) - (ballPosition.x - ballRadius)))bounceSide.right = false;
							else bounceSide.down = false;
						}
					}
					if (bounceSide.up==true)
					{
						if (bounceSide.left==true)
						{
							if (((ballPosition.y + ballRadius)- (Brick[i].y))< ((ballPosition.x + ballRadius) - (Brick[i].x)))bounceSide.left = false;
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
					if (bounceSide.down == true && ballSpeed.y< 0) invertY= true;
					if (bounceSide.up == true && ballSpeed.y> 0) invertY= true;
					bounceSide.up = false;
					bounceSide.down = false;
					bounceSide.left = false;
					bounceSide.right = false;
				}
				if (invertY == true)ballSpeed.y *= -1.0f;
				if (invertX == true)ballSpeed.x *= -1.0f;
				invertX = false;
				invertY = false;
					/*
					if (((ballPosition.y - ballRadius) <= (Brick[i].y + Brick[i].height)) &&
						((ballPosition.y - ballRadius) > (Brick[i].y + Brick[i].height + ballSpeed.y)) &&
						((fabs(ballPosition.x - Brick[i].x - Brick[i].width / 2)) < (Brick[i].width / 2 + ballRadius * 2 / 3)) && (ballSpeed.y < 0))
					{
						BrickExists[i] = false;
						ballSpeed.y *= -1;
					}
					else if (((ballPosition.y + ballRadius) >= (Brick[i].y)) &&
						((ballPosition.y + ballRadius) < (Brick[i].y + ballSpeed.y)) &&
						((fabs(ballPosition.x - Brick[i].x - Brick[i].width / 2)) < (Brick[i].width / 2 + ballRadius * 2 / 3)) && (ballSpeed.y > 0))
					{
						BrickExists[i] = false;
						ballSpeed.y *= -1;
					}
					else if (((ballPosition.x + ballRadius) >= (Brick[i].x)) &&
						((ballPosition.x + ballRadius) < (Brick[i].x + ballSpeed.x)) &&
						((fabs(ballPosition.y - Brick[i].y - Brick[i].height / 2)) < (Brick[i].height / 2 + ballRadius * 2 / 3)) && (ballSpeed.x > 0))
					{
						BrickExists[i] = false;
						ballSpeed.x *= -1;
					}
					else if (((ballPosition.x - ballRadius) <= (Brick[i].x + Brick[i].width)) &&
						((ballPosition.x - ballRadius) > (Brick[i].x + Brick[i].width + ballSpeed.x)) &&
						((fabs(ballPosition.y - Brick[i].y - Brick[i].height / 2)) < (Brick[i].height / 2 + ballRadius * 2 / 3)) && (ballSpeed.x < 0))
					{
						BrickExists[i] = false;
						ballSpeed.x *= -1;
					}
					*/
				
			}
		}
		else framesCounter++;

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("Lives left: %i", player.vidas ), 40 ,GetScreenHeight()- 40, 20, GRAY);
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
		DrawCircleV(ballPosition, ballRadius, YELLOW);
		DrawRectangle(player.rectangle.x, player.rectangle.y, player.rectangle.width, player.rectangle.height, GREEN);

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
