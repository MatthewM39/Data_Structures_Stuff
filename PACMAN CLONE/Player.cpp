#include "Game.h"
#include "Player.h"

Player::Player(Game * game, int x, int y) : Actor(game, x, y){ // set pointer to game, starting x and y coords
	lives = 3; // player gets 3 lives
	score = 0; // 0 starting score
	setDisplayChar('@');
	setColor(black, red);
	
}

int Player::getLives() const{
	return lives;
}

int Player::getScore() const
{
	return score;
}

void Player::increaseScore(int x) {
	score = score + x;
}

void Player::decreaseLives(){
	lives--;
}

void Player::move() {
	char temp; // temp char to be set equal to the possible input
	char mazeVal; // char to store the value in the maze at a coord
	Direction myDir; // player's current direction
	
	if (myGame->getCharInput(temp)) { // need to check for char input

		if (temp == '4') { // direction is found to be left
			mazeVal = myGame->getMazeContents(xPos - 1, yPos); // set maze val equal to the space the player wants to move
			if(mazeVal != '#' && mazeVal != '%') // make sure that space is legal
				setDirection(Left); // if it is, set the new direction
		}

		else if (temp == '6') { // direction is right... similar code
			mazeVal = myGame->getMazeContents(xPos + 1, yPos);
			if (mazeVal != '#' && mazeVal != '%')
				setDirection(Right);
		}

		else if (temp == '8') { // direction is up
			mazeVal = myGame->getMazeContents(xPos, yPos - 1); //tempY - 1, because increasing the value of Y moves down on the map 
			if (mazeVal != '#' && mazeVal != '%')
				setDirection(Up);
		}

		else if (temp == '2') { // direction is down
			mazeVal = myGame->getMazeContents(xPos, yPos + 1);
			if (mazeVal != '#' && mazeVal != '%')
				setDirection(Down);
		}

		else
			myGame->cheatCodes(temp);
	}

	myDir = getDirection(); // get the players new direction

	if (myDir == Left) { // to move left, make sure the place the player wants to move is legal
		mazeVal = myGame->getMazeContents(xPos - 1, yPos);
		if (mazeVal != '#' && mazeVal != '%') {
			xPos = xPos - 1;
		}
		else
			resetDir(); // space isn't legal, need to reset the direction
	}

	else if (myDir == Right) {
		mazeVal = myGame->getMazeContents(xPos + 1, yPos);
		if (mazeVal != '#' && mazeVal != '%') {
			xPos = xPos + 1;
		}
		else
			resetDir();
	}

	else if (myDir == Up) {
		mazeVal = myGame->getMazeContents(xPos, yPos - 1);
		if (mazeVal != '#' && mazeVal != '%') {
			yPos = yPos - 1;
		}
		else
			resetDir();
	}

	else if (myDir == Down) {
		mazeVal = myGame->getMazeContents(xPos, yPos + 1);
		if (mazeVal != '#' && mazeVal != '%') {
			yPos = yPos + 1;
		}
		else
			resetDir();
	}

}

void Player::incrementLife() {
	lives++;
}