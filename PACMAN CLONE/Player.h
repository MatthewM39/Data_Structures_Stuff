#ifndef PLAYER
#define PLAYER
#include "Actor.h"

class Game;

class Player : public Actor {

public: // these are public because game needs acess to them in order to do anything with the player

	Player(Game * game, int x, int y); // constructor needs to set myGame equal to game, lives to 3, score to 0

	int getLives() const; // get number of lives

	int getScore() const; // return score

	void increaseScore(int x); // increase score

	void decreaseLives(); // decrement lives by 1

	void incrementLife(); // gain a life!

	void move(); // movement for the player class. 
	
private:
	int lives; // store number of lives
	int score; // player score
};

#endif
