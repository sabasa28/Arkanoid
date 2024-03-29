#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace arkanoid_IDG {

	extern bool ActiveBarrier;
	
	enum lvl {
		lvl1,
		lvl2,
		lvl3,
		lvl4
	};
	extern lvl level;
	
	extern bool pause;
	
	void initPause();
	void updateGameplay();
	void drawGameplay();
}
#endif //GAMEPLAY_H

