#include "console.h"

#include "raylib.h"
namespace arkanoid_IDG {
	int screenWidth = 800;
	int screenHeight = 450;

	int framesCounter = 0;

	const int windowSize1_x = 800;
	const int windowSize1_y = 450;
	const int windowSize2_x = 1200;
	const int windowSize2_y = 675;

	void initConsole()
	{
		SetExitKey(NULL);
		InitWindow(screenWidth, screenHeight, "Arkanoid raylib- Inaki Diez");//Iñaki
		InitAudioDevice();
	}
}