#ifndef MENU_H
#define MENU_H

#include "raylib.h"
extern Rectangle Jugar;
extern Rectangle Opciones;
extern Rectangle Salir;
struct TextDivider
{
	float x;
	float y;
	float font;
};
extern TextDivider playText;
extern TextDivider optionsText;
extern TextDivider exitText;

extern int opciones;
extern Color selectedOption;
extern Color notSelectedOption;
extern Color selectedText;
extern Color notSelectedText;

void initMenu();
void executeMenu();

#endif //MENU_H
