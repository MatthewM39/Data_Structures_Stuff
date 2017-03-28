#ifndef MONSTER
#define MONSTER
#include "Actor.h"
#include "Maze.h"

enum State { Normal, Dead, Vulnerable }; // enum for the states

class Monster : public Actor { // child of Actor

public: // these methods are public because they are utilized mainly by Game to manage the actor

	Monster(Game * game, int x, int y, Maze * maze);

	State getState() const;  // get the monster's state

	void setState(State toSet); // set a monster's state

	char getDisplayChar(Color &fg, Color &bg) const; // override of the Actor one, intuitively returns the colors of the monster

	void setTicks(int ticks); // set the amount of ticks vulnerable

	void decTicks(); // decrement said ticks

	void clearSteps(); // clear the number of steps

	virtual void move(); // pure virtual, children need to implement movement if they want it

protected:
	Maze * myMaze; // pointer to maze. children need access to it
	int steps; // number of steps left. children need to be able to access it b/c Monster is abstract and implements no movement ai.

private:
	State myState; // the monster's state. 
	int vulnerableTicks; // number of ticks the monster has until they become normal. game accesses it with setTicks and decTicks.
};
#endif