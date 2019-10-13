#ifndef CODINGTOOLS_H
#define CODINGTOOLS_H
#include "raylib.h"
struct Button
{
	Rectangle rectangle;
	Rectangle divider;
	Vector2 textDivider;
	Vector2 textPos;
	int textFont;
	float textFontDivider;
	Color color;
	Color textColor;
};
extern Color selectedOption;
extern Color notSelectedOption;
extern Color selectedText;
extern Color notSelectedText;
#endif //CODINGTOOLS_H

