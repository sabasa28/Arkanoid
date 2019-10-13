#ifndef GAME_H
#define GAME_H

enum State
{
	menu,
	options,
	resetingValues,
	gameplay,
	finalScreen,
	closing
};
extern State gamestate;
extern State lastState;
void init();
#endif //GAME_H
