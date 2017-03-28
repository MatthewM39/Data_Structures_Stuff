#ifndef STINKY
#define STINKY
#include "Clyde.h"

class Stinky : public Clyde { // Stinky is a child of Clyde!

public:
	Stinky(Game * game, int x, int y, Maze * maze);
	virtual void move(); // virtual so that it can potentially be overwritten
protected:
	void reverseDirection(); // attempts to avoid the current direction. protected so that children can use it when necessary.
	void panicCheck(Direction d1, Direction d2, Direction d3); // attempts to reverse from a direction, or go any way but a direction
};
#endif
