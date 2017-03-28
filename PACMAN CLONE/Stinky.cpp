#include "Stinky.h"
#include "Game.h"

Stinky::Stinky(Game * game, int x, int y, Maze * maze) : Clyde(game, x, y, maze){
	setDisplayChar('S');
	setColor(purple, black);
	myDirection = None;
}

void Stinky::move(){
	if(getState() == Normal)
		Clyde::normalMove(); // copy clyde's normal movement
	else if (getState() == Vulnerable) { 
		if(checkSteps())	reverseDirection(); // player found, need to reverse direction
		if (myGame->checkMaze(xPos, yPos, 1, myDirection))
			cardinalMove(1, myDirection); // move in a direction
		else {
			steps = 0;
			Inky::move();
		}
	}
	else
		Inky::deadMove(); // stinky is dead
}

void Stinky::reverseDirection() {
	if (steps == 5) { //  make sure steps is 5
		if (myDirection == Up)	panicCheck(Down, Left, Right);
		else if (myDirection == Down)	panicCheck(Up, Left, Right);
		else if (myDirection == Left)	panicCheck(Right, Left, Down);
		else if (myDirection == Right)	panicCheck(Left, Up, Down);
	}
}

void Stinky::panicCheck(Direction d1, Direction d2, Direction d3){
	if (myGame->checkMaze(xPos, yPos, 1, d1)) 
		myDirection = d1;
	else if (myGame->checkMaze(xPos, yPos, 1, d2))
		myDirection = d2;
	else if (myGame->checkMaze(xPos, yPos, 1, d3))
		myDirection = d3;
}