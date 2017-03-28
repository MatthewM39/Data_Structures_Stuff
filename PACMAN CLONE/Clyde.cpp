#include "Clyde.h"
#include "Game.h"

Clyde::Clyde(Game * game, int x, int y, Maze * maze) : Inky(game, x, y, maze) {
	setDisplayChar('C'); // set his display char
	setColor(blue, black); // and his colors
	myDirection = None;
}

void Clyde::move(){
	if (getState() == Normal) { // normal state, need to use normal move code for Clyde
		normalMove();
	}
	else 
		Inky::move(); // clyde is vulnerable or dead, so default to inky's code
}

void Clyde::normalMove() {

	checkSteps();
	if (myGame->checkMaze(xPos, yPos, 1, myDirection) && steps > 0) // move in current direction
		cardinalMove(1, myDirection);
	else // player isn't in sight or you hit a wall, move like dumb inky
		Inky::move();
}

bool Clyde::checkSteps() {

		int random = 0; 
		Direction tempDir;
		sightMove(random, tempDir); // call sightMove to get a random and a direction
		if (random > 1) { // random is above the threshold, player is found and you're lucky
			steps = 5;  // set steps to five
			myDirection = tempDir; // set selected direction
			return true;
		}

	return false;
}

void Clyde::sightMove(int &r, Direction &dir) {
	bool wallFound = false; // bool for no wall between the player and Clyde
	int x = myGame->getPlayerX(); // get player x
	int y = myGame->getPlayerY(); // get player y
	if (xPos == x) { // player and clyde are in the same horizontal row
		wallFound = myMaze->betweenY(x, y, yPos, '#'); // call betweenY to see if a wall exists between the player and clyde
		if (!wallFound) { // no wall between!
			if (x > xPos)	dir = Right; // player is more right, move more right
			else if (x < xPos) dir = Left; // player is lefter, set direction to left
			r = rand() % 4;
		}
	}
	else if (yPos == y) { // parallel of above, but in the same column
		wallFound = myMaze->betweenX(y, x, xPos, '#'); // call betweenX instead
		if (!wallFound) {
			if (y > yPos) dir = Down;
			else if (y < yPos) dir = Up;
			r = rand() % 4;
		}
	}
}