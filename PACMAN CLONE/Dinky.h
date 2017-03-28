#ifndef DINKY
#define DINKY
#include "Stinky.h"


class Dinky : public Stinky{ // Dinky is a child of Stinky

public:
	Dinky(Game * game, int x, int y, Maze * maze); // constructor
	void move(); // overwritten move function. no children, no need for virtual
	void setRun(); // sets the bool isRunning to false. public so game can access it
private:
	/** I made these two variables below private because Dinky is at the bottom of the inheritance tree. There's no reason
	anyone else would ever need to access these variables.
	**/
	int myMap[23][21];  // map with the fastest route to the player
	bool isRunning; // if Dinky is running from the player (vulnerable and in sight!). private because only Dinky should access it.
};
#endif