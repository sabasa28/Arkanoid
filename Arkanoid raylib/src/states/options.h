#ifndef OPTIONS_H
#define OPTIONS_H

#include "raylib.h"

#include "general_elements/codingTools.h"

extern Button MuteVolume;
extern Button SwapScreensize1;
extern Button SwapScreensize2;
extern Button SwapScreensize3;
extern Button Back;

extern int optionCounterOptions;

void initOptions();
void updateOptions();
void drawOptions();
#endif //OPTIONS_H

