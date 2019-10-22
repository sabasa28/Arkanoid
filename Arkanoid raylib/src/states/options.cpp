#include "options.h"

#include "raylib.h"

#include "general_elements/codingTools.h"
#include "general_elements/console.h"
#include "states/game.h"
#include "states/gameplay.h"
#include "resetGameElements.h"
#include "assets/images.h"
#include "assets/sound.h"

namespace arkanoid_IDG {

	static bool muted=false;
	static Button MuteVolume;
	static Button SwapScreensize1;
	static Button SwapScreensize2;
	static Button SwapScreensize3;
	static Button Back;
	static int optionCounterOptions = 5;
	static int lastScreenSizeX;
	static int lastScreenSizeY;
	void resizeScreen(int width, int height);
	void resizeScreen(int width, int height);
	void resizeToFullscreen();
	bool fullscreenIsActivated();

	void initOptions()
	{
		MuteVolume.divider.x = 3.1f;
		MuteVolume.divider.y = 5.2f;
		MuteVolume.divider.width = 2.5f;
		MuteVolume.divider.height = 6.0f;
		MuteVolume.textFontDivider = 10.0f;
		MuteVolume.textDivider.x = 2.9f;
		MuteVolume.textDivider.y = 4.5f;
		MuteVolume.rectangle.x = screenWidth / MuteVolume.divider.x;
		MuteVolume.rectangle.y = screenHeight / MuteVolume.divider.y;
		MuteVolume.rectangle.width = screenWidth / MuteVolume.divider.width;
		MuteVolume.rectangle.height = screenHeight / MuteVolume.divider.height;
		MuteVolume.textFont = static_cast<int>(screenHeight / MuteVolume.textFontDivider);
		MuteVolume.textPos.x = screenWidth / MuteVolume.textDivider.x;
		MuteVolume.textPos.y = screenHeight / MuteVolume.textDivider.y;
		SwapScreensize1.divider.x = 2.8f;
		SwapScreensize1.divider.y = 2.5f;
		SwapScreensize1.divider.width = 3.0f;
		SwapScreensize1.divider.height = 8.0f;
		SwapScreensize1.textFontDivider = 15.0f;
		SwapScreensize1.textDivider.x = 2.5f;
		SwapScreensize1.textDivider.y = 2.3f;
		SwapScreensize1.rectangle.x = screenWidth / SwapScreensize1.divider.x;
		SwapScreensize1.rectangle.y = screenHeight / SwapScreensize1.divider.y;
		SwapScreensize1.rectangle.width = screenWidth / SwapScreensize1.divider.width;
		SwapScreensize1.rectangle.height = screenHeight / SwapScreensize1.divider.height;
		SwapScreensize1.textFont = static_cast<int>(screenHeight / SwapScreensize1.textFontDivider);
		SwapScreensize1.textPos.x = screenWidth / SwapScreensize1.textDivider.x;
		SwapScreensize1.textPos.y = screenHeight / SwapScreensize1.textDivider.y;
		SwapScreensize2.divider.y = 1.8f;
		SwapScreensize2.textDivider.y = 1.7f;
		SwapScreensize2.rectangle.x = SwapScreensize1.rectangle.x;
		SwapScreensize2.rectangle.y = screenHeight / SwapScreensize2.divider.y;
		SwapScreensize2.rectangle.width = SwapScreensize1.rectangle.width;
		SwapScreensize2.rectangle.height = SwapScreensize1.rectangle.height;
		SwapScreensize2.textFont = SwapScreensize1.textFont;
		SwapScreensize2.textPos.x = SwapScreensize1.textPos.x;
		SwapScreensize2.textPos.y = screenHeight / SwapScreensize2.textDivider.y;
		SwapScreensize3.divider.y = 1.4f;
		SwapScreensize3.textDivider.y = 1.35f;
		SwapScreensize3.rectangle.x = SwapScreensize1.rectangle.x;
		SwapScreensize3.rectangle.y = screenHeight / SwapScreensize3.divider.y;
		SwapScreensize3.rectangle.width = SwapScreensize1.rectangle.width;
		SwapScreensize3.rectangle.height = SwapScreensize1.rectangle.height;
		SwapScreensize3.textFont = SwapScreensize1.textFont;
		SwapScreensize3.textPos.x = SwapScreensize1.textPos.x;
		SwapScreensize3.textPos.y = screenHeight / SwapScreensize3.textDivider.y;
		Back.divider.x = 2.5f;
		Back.divider.y = 1.17f;
		Back.textDivider.x = 2.1f;
		Back.textDivider.y = 1.13f;
		Back.divider.width = 4.0f;
		Back.rectangle.x = screenWidth / Back.divider.x;
		Back.rectangle.y = screenHeight / Back.divider.y;
		Back.rectangle.width = screenWidth / Back.divider.width;
		Back.rectangle.height = SwapScreensize1.rectangle.height;
		Back.textFont = SwapScreensize1.textFont;
		Back.textPos.x = screenWidth / Back.textDivider.x;
		Back.textPos.y = screenHeight / Back.textDivider.y;
	}


	void updateOptions()
	{
		UpdateMusicStream(originalMusic);

		if (IsKeyPressed(KEY_DOWN))optionCounterOptions--;
		if (IsKeyPressed(KEY_UP))optionCounterOptions++;
		if (optionCounterOptions < 1)optionCounterOptions = 5;
		if (optionCounterOptions > 5)optionCounterOptions = 1;


		if (optionCounterOptions == 1)
		{
			MuteVolume.color = notSelectedOption;
			SwapScreensize1.color = notSelectedOption;
			SwapScreensize2.color = notSelectedOption;
			SwapScreensize3.color = notSelectedOption;
			Back.color = selectedOption;
			MuteVolume.textColor = notSelectedText;
			SwapScreensize1.textColor = notSelectedText;
			SwapScreensize2.textColor = notSelectedText;
			SwapScreensize3.textColor = notSelectedText;
			Back.textColor = selectedText;
			if (IsKeyPressed(KEY_ENTER))
			{
				gamestate = lastState;
			}
		}

		if (optionCounterOptions == 2)
		{
			MuteVolume.color = notSelectedOption;
			SwapScreensize1.color = notSelectedOption;
			SwapScreensize2.color = notSelectedOption;
			SwapScreensize3.color = selectedOption;
			Back.color = notSelectedOption;
			MuteVolume.textColor = notSelectedText;
			SwapScreensize1.textColor = notSelectedText;
			SwapScreensize2.textColor = notSelectedText;
			SwapScreensize3.textColor = selectedText;
			Back.textColor = notSelectedText;
			if (IsKeyPressed(KEY_ENTER))
			{
				resizeToFullscreen();
			}
		}

		if (optionCounterOptions == 3)
		{
			MuteVolume.color = notSelectedOption;
			SwapScreensize1.color = notSelectedOption;
			SwapScreensize2.color = selectedOption;
			SwapScreensize3.color = notSelectedOption;
			Back.color = notSelectedOption;
			MuteVolume.textColor = notSelectedText;
			SwapScreensize1.textColor = notSelectedText;
			SwapScreensize2.textColor = selectedText;
			SwapScreensize3.textColor = notSelectedText;
			Back.textColor = notSelectedText;
			if (IsKeyPressed(KEY_ENTER))
			{
				resizeScreen(windowSize2_x,windowSize2_y);
			}
		}

		if (optionCounterOptions == 4)
		{
			MuteVolume.color = notSelectedOption;
			SwapScreensize1.color = selectedOption;
			SwapScreensize2.color = notSelectedOption;
			SwapScreensize3.color = notSelectedOption;
			Back.color = notSelectedOption;
			MuteVolume.textColor = notSelectedText;
			SwapScreensize1.textColor = selectedText;
			SwapScreensize2.textColor = notSelectedText;
			SwapScreensize3.textColor = notSelectedText;
			Back.textColor = notSelectedText;
			if (IsKeyPressed(KEY_ENTER))
			{
				resizeScreen(windowSize1_x, windowSize1_y);
			}
		}

		if (optionCounterOptions == 5)
		{
			MuteVolume.color = selectedOption;
			SwapScreensize1.color = notSelectedOption;
			SwapScreensize2.color = notSelectedOption;
			SwapScreensize3.color = notSelectedOption;
			Back.color = notSelectedOption;
			MuteVolume.textColor = selectedText;
			SwapScreensize1.textColor = notSelectedText;
			SwapScreensize2.textColor = notSelectedText;
			SwapScreensize3.textColor = notSelectedText;
			Back.textColor = notSelectedText;
			if (IsKeyPressed(KEY_ENTER))
			{
				if(muted)SetMasterVolume(0.1f);
				else SetMasterVolume(0.0f);
				if(muted==true) muted=false;
				else muted = true;
			}
		}

	}

	void drawOptions()
	{
		BeginDrawing();
		DrawTexture(background, 0, 0, WHITE);
		DrawRectangle(static_cast<int>(MuteVolume.rectangle.x), static_cast<int>(MuteVolume.rectangle.y), static_cast<int>(MuteVolume.rectangle.width), static_cast<int>(MuteVolume.rectangle.height), MuteVolume.color);
		DrawText("Mute sounds", static_cast<int>(MuteVolume.textPos.x), static_cast<int>(MuteVolume.textPos.y), MuteVolume.textFont, MuteVolume.textColor);
		DrawRectangle(static_cast<int>(SwapScreensize1.rectangle.x), static_cast<int>(SwapScreensize1.rectangle.y), static_cast<int>(SwapScreensize1.rectangle.width), static_cast<int>(SwapScreensize1.rectangle.height), SwapScreensize1.color);
		DrawText("Screensize 1", static_cast<int>(SwapScreensize1.textPos.x), static_cast<int>(SwapScreensize1.textPos.y), SwapScreensize1.textFont, SwapScreensize1.textColor);
		DrawRectangle(static_cast<int>(SwapScreensize2.rectangle.x), static_cast<int>(SwapScreensize2.rectangle.y), static_cast<int>(SwapScreensize2.rectangle.width), static_cast<int>(SwapScreensize2.rectangle.height), SwapScreensize2.color);
		DrawText("Screensize 2", static_cast<int>(SwapScreensize2.textPos.x), static_cast<int>(SwapScreensize2.textPos.y), SwapScreensize2.textFont, SwapScreensize2.textColor);
		DrawRectangle(static_cast<int>(SwapScreensize3.rectangle.x), static_cast<int>(SwapScreensize3.rectangle.y), static_cast<int>(SwapScreensize3.rectangle.width), static_cast<int>(SwapScreensize3.rectangle.height), SwapScreensize3.color);
		DrawText("Screensize 3", static_cast<int>(SwapScreensize3.textPos.x), static_cast<int>(SwapScreensize3.textPos.y), SwapScreensize3.textFont, SwapScreensize3.textColor);
		DrawRectangle(static_cast<int>(Back.rectangle.x), static_cast<int>(Back.rectangle.y), static_cast<int>(Back.rectangle.width), static_cast<int>(Back.rectangle.height), Back.color);
		DrawText("Back", static_cast<int>(Back.textPos.x), static_cast<int>(Back.textPos.y), Back.textFont, Back.textColor);
		EndDrawing();
	}
	
	void resizeScreen(int width, int height)
	{
		if (fullscreenIsActivated())
		{
			ToggleFullscreen();
		}
		lastScreenSizeX = screenWidth;
		lastScreenSizeY = screenHeight;
		screenWidth = width;
		screenHeight = height;
		SetWindowSize(screenWidth, screenHeight);
		SetWindowPosition((GetMonitorWidth(0) - screenWidth) / 2, (GetMonitorHeight(0) - screenHeight) / 2);
		resizeInit(static_cast<float>(width)/lastScreenSizeX,static_cast<float>(height)/lastScreenSizeY,static_cast<float>(width+height)/(lastScreenSizeX+lastScreenSizeY));
	}

	void resizeToFullscreen()
	{
		lastScreenSizeX = screenWidth;
		lastScreenSizeY = screenHeight;
		screenWidth = GetMonitorWidth(0);
		screenHeight = GetMonitorHeight(0);
		ToggleFullscreen();
		SetWindowSize(screenWidth, screenHeight);
		resizeInit(static_cast<float>(screenWidth) / lastScreenSizeX, static_cast<float>(screenHeight) / lastScreenSizeY, static_cast<float>(screenWidth + screenHeight) / (lastScreenSizeX + lastScreenSizeY));
	}

	bool fullscreenIsActivated()
	{
		return screenWidth == GetMonitorWidth(0);
	}
}