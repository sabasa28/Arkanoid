#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
namespace arkanoid_IDG {
	
	struct Player
	{
		Rectangle rectangle;
		Rectangle divider;
		float speed;
		float speedDivider;
		float centerPosition;
		bool ballAttached = true;
		int lives;
		int pieces = 12;
		float regularSpeed;
	};
	extern Player player;

	enum Scorestate
	{
		lost,
		won,
		playing
	};
	extern Scorestate scorestate;

	float GetCenterPos(Player player);
	void initPlayer();
}
#endif // PLAYER_H