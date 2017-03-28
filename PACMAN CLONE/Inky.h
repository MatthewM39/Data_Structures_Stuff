#ifndef INKY
#define INKY
#include "Monster.h"

class Inky : public Monster { // child of Monster

public:
	Inky(Game * game, int x, int y, Maze * maze);

	virtual void move(); // overwritten by Inky, children may overwrite as well

protected:
	void cardinalMove(int n, Direction dir); // moves in a cardinal direction. protected so any inky can easily move a coord
	void deadMove(); // movement for return to spawn. protected so any inky or child can easily return to spawn
};
#endif