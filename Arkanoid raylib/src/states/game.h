#ifndef GAME_H
#define GAME_H

enum State
{
	menu,
	optionsMenu,
	resetingValues,
	gameplay,
	gameOver,
	closing
};
extern State gamestate;
extern State lastState;
void init();
void executeGame();
#endif //GAME_H
