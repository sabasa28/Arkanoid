#include "powerUP.h"

#include "raylib.h"

#include <cmath>

#include "game_elements/player.h"
#include "game_elements/ball.h"
#include "general_elements/console.h"

namespace arkanoid_IDG {
	static int auxRandom = 0;
	static const int maxTpDistance = 200;
	static const int minTpDistance = 100;
	Rectangle barrierRec;
	float barrierHeightDiv = 225.0f;

	void initPowerUps() 
	{
		barrierRec.width = screenWidth;
		barrierRec.height = screenHeight / barrierHeightDiv;
		barrierRec.x = 0;
		barrierRec.y = screenHeight-barrierRec.height;
	}

	void playerToRandomX()
	{
		while (fabs(player.rectangle.x - auxRandom)>maxTpDistance || fabs(player.rectangle.x - auxRandom)<minTpDistance )
		{
			auxRandom = GetRandomValue(0, screenWidth - player.rectangle.width);
		}
		player.rectangle.x = auxRandom;
	}

	void divideBallRadius()
	{
		if (ball.sizeState != shrinked2)
		{
			ball.radius /= 2;
			switch (ball.sizeState)
			{
			case enlarged2:
				ball.sizeState = enlarged1;
				break;
			case enlarged1:
				ball.sizeState = normalSize;
				break;
			case normalSize:
				ball.sizeState = shrinked1;
				break;
			case shrinked1:
				ball.sizeState = shrinked2;
				break;
			}
		}
	}

	void multiplyBallRadius()
	{
		if (ball.sizeState != enlarged2)
		{
			ball.radius *= 2;
			switch (ball.sizeState)
			{
			case shrinked2:
				ball.sizeState = shrinked1;
				break;
			case shrinked1:
				ball.sizeState = normalSize;
				break;
			case normalSize:
				ball.sizeState = enlarged1;
				break;
			case enlarged1:
				ball.sizeState = enlarged2;
				break;
			}
		}
	}

	void divideSpeeds(bool isSlowed)
	{
		if (isSlowed==false)
		{
			player.speed /= 2;
			ball.speed.x /= 2;
			ball.speed.y /= 2;
		}
	}
	void resetSpeeds()
	{
		player.speed *= 2;
		ball.speed.x *= 2;
		ball.speed.y *= 2;
	}
}