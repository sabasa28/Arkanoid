#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "codingTools.h"

extern Button Play;
extern Button Opciones;
extern Button Salir;
struct TextDivider
{
	float x;
	float y;
	float font;
};
extern TextDivider playText;
extern TextDivider optionsText;
extern TextDivider exitText;

extern int optionMenu;

void initMenu();
void executeMenu();

#endif //MENU_H
