#include "Inky.h"
#include "Game.h"

Inky::Inky(Game * game, int x, int y, Maze * maze) : Monster(game, x, y, maze){
	setDisplayChar('I');
	setColor(cyan, black);
	myDirection = None;
}

void Inky::move() {
	if (getState() != Dead) { // Normal and no direction
		if (myDirection == None || steps == 0) { // time to pick a new direction
			while (myDirection == None) { // get a random moveable direction
				int x = rand() % 4; // generate the direction
				Direction myDir;
				switch (x) {
				case 0:
					myDir = Up;
					break;
				case 1:
					myDir = Down;
					break;
				case 2:
					myDir = Left;
					break;
				case 3:
					myDir = Right;
					break;
				}
				if (myGame->checkMaze(xPos, yPos, 1, myDir) == true) // ensure there isn't a wall in a direction
					myDirection = myDir; // if not, myDirection is still None so reloop
			}
			steps = 1 + rand() % (4 - 1 + 1); // random value for steps once direction is found
		}

		if (myGame->checkMaze(xPos, yPos, 1, myDirection)) { // attempt to move in a direction
			cardinalMove(1, myDirection);
		}

		else // can't move, reset direction and recursive call to get a new direction and move
		{
			myDirection = None;
			move();
		}
	}
	else
		deadMove(); // dead monster, so use deadMove
}

void Inky::cardinalMove(int n, Direction dir) { // move in a direction. 
	if (dir == Up)
		yPos = yPos - n;
	else if (dir == Down)
		yPos = yPos + n;
	else if (dir == Left)
		xPos = xPos - n;
	else if (dir == Right)
		xPos = xPos + n;
	steps--; // decrease steps by 1
	if (steps == 0) // when steps is 0, a monster loses direction
		setDirection(None);
}

void Inky::deadMove() {
	myMaze->getNextCoordinate(xPos, yPos); // move to a point closer to spawn
	if (myMaze->getMazeDist(xPos, yPos) == 0 && getState() == Dead) { // check if at spawn
		setState(Normal); // if so, time to respawn
		setColor(Actor::getColor(), black); // swap colors back to default
	}
}