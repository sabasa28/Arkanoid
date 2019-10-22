#ifndef GAME_H
#define GAME_H

namespace arkanoid_IDG {

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

	void resizeInit(float multiplierX, float multiplierY, float multiplierXY);
	void executeGame();
}

#endif //GAME_H
