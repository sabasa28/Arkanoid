#ifndef MENU_H
#define MENU_H

#include "raylib.h"

#include "general_elements/codingTools.h"
namespace arkanoid_IDG {
	extern Button playbutton;
	extern Button optionsbutton;
	extern Button exitbutton;
	struct TextDivider
	{
		float x;
		float y;
		float font;
	};

	extern int optionCounterMenu;

	void initMenu();
	void updateMenu();
	void drawMenu();
}
#endif //MENU_H
