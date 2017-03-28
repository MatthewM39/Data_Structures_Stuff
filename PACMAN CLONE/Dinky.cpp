#include "Dinky.h"
#include "Game.h"
Dinky::Dinky(Game * game, int x, int y, Maze * maze) : Stinky (game, x, y, maze){
	setDisplayChar('D');
	setColor( blue , black);
	myDirection = None;
	isRunning = false; // can't be running from the player at the start
}

void Dinky::move() {
	if (getState() == Normal) {
		if (isRunning)	isRunning = false; // if normal , no need to run anymore if running
		if (steps > 0) { // continue on outdated path
			myMaze->getNextCoordinate(myMap, xPos, yPos);
			steps--; // need to manually decrease steps since cardinalMove isn't called
			if (myMap[xPos][yPos] == 0) { // destination is reached
				steps = 0;
			}
		}
		else { // no steps left, compute shortest distance to player's coords
			myMaze->computeDistance(myMap, myGame->getPlayerX(), myGame->getPlayerY());
			steps = 15; // take that path for 15 steps
		}
	}
	else if (getState() == Vulnerable) { // Dinky is vulnerable
		if (!isRunning) { // if dinky isn't running from the player already, need to check for player
			int r = -1;
			sightMove(r, myDirection); // find the player
			if (r > -1) { // player is found
				steps = 5; // move for 5 steps 
				reverseDirection(); // reverse the direction so you don't move towards the player
				isRunning = true; 
				cardinalMove(1, myDirection);
			}
			else {
				Inky::deadMove(); // player isn't in sight, so take the fastest path to the spawn (b/c it's safe)
				steps--; // manually decrement steps. no call to cardinalMove, no automatic step decrement
			}
		}
		else { // dinky is running
			if (myGame->checkMaze(xPos, yPos, 1, myDirection)) { // attempt to move in current direction
				cardinalMove(1, myDirection);
			}
			else { // can't run in current direction. recheck player visibility
				isRunning = false;
				move(); // recursive call
				}
			}
	}
	else { // Dinky is dead
		if (isRunning) isRunning = false;
		Inky::deadMove();
	}
}

void Dinky::setRun() { 
	isRunning = false;
}