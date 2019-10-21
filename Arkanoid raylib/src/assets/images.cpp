#include "images.h"

#include "raylib.h"

#include "general_elements/console.h"
namespace arkanoid_IDG {
	static Image originalImage;
	Texture background;

	void initTextures()
	{
		originalImage = LoadImage("images/arkanoid_background.jpg");
		ImageResize(&originalImage, screenWidth, screenHeight);
		background = LoadTextureFromImage(originalImage);
		UnloadImage(originalImage);
	}

	void unloadTextures()
	{
		UnloadTexture(background);
	}
}