#ifndef CLYDE
#define CLYDE
#include "Inky.h"


class Clyde : public Inky{ // child of Inky

public:
	Clyde(Game * game, int x, int y, Maze * maze); // constructor for Clyde

	virtual void move(); // it's public so that the game can move Clyde. virtual b/c overwritten. calls normalMove() potentially

protected:
	/**these three are private because these "AI" methods are used by Clyde and his children
	 splitting into 3 methods was convenient, so you can only call what is needed in other methods
	 splitting the AI into three methods lets you pick and choose which abilities you want the
	 movement to have for a child
	 **/
	void normalMove(); // calls checkSteps to see if direction needs to change, moves in player's direction, or random (if player isnt in sight)

	void sightMove(int &r, Direction & dir); // check to see if the player is in the line of sight

	bool checkSteps(); // if player is found in sight, handles setting Clyde's direction. 

};
#endif