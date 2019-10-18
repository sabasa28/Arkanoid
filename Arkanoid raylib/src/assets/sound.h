#ifndef SOUNDS_H
#define SOUNDS_H

#include "raylib.h"
namespace arkanoid_IDG {
	extern Music originalMusic;
	extern Music originalMusic1;
	extern Sound originalSound;
	void initSounds();
	void resetSounds();
	void unloadSounds();
}
#endif //SOUNDS_H