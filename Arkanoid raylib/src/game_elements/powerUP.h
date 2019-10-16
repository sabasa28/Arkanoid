#ifndef POWERUP_H
#define POWERUP_H

#include "raylib.h"

namespace arkanoid_IDG {
	extern Rectangle barrierRec;
	void initPowerUps();
	void playerToRandomX();
	void divideBallRadius();
	void multiplyBallRadius();
	void divideSpeeds(bool isSlowed);
	void resetSpeeds();
}
#endif // POWERUP_H

