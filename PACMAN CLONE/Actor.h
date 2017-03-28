#ifndef ACTOR
#define ACTOR
#include "CConsole.h"

class Game;

class Actor{

public:

	Actor(Game * game, int x, int y); // constructor sets myGame equal to game. also passes starting coords

	enum Direction { Up = 0, Down = 1, Left = 2, Right = 3, None = 4 }; // possible directions for the actor

	int getX() const; // return xPos. public for easy access in game
	int getY() const; // return yPos. public for easy access in game

	Color getColor() const; // get the foreground color. public for easy access.
	Color getBgColor() const; // get the background color public for easy access.

	virtual char getDisplayChar() const; // get char displayed by an actor. virtual because it changes for monster and public so game can display actors.

	Direction getDirection() const; // return the current direction... public for game acess

	void setX(int x); // set xPos. public for easy access. game needs a way to put a monster back at spawn

	void setY(int y); // set yPos. public for easy access. game needs a way to put a monster back at spawn

	void resetDir(); // reset actor direction to None. public for easy access. game needs a way to reset the actors

	void setColor(Color fg, Color bg); // set the fg and bg colors. game needs to change monsters when the player eats super pellets

	virtual void move(); // move the actor... different for monsters and player. pure because it's abstract

private:
	char toDisplay; // char to display. private
	Color dColor, bgColor; // display color of an actor and its background color. private

protected:
	Game * myGame; // pointer to game, needs to be protected so its children can use it. protected so children may use when necessary.
	void setDisplayChar(char ch); // modify the display char. protected b/c only actors or its children should be changing their display chars.
	void setDirection(Direction d); // set the actor direction. only an actor or its child would need to change its direction.
	Direction myDirection; // current direction of the actor
	int xPos, yPos; // x and y coords for actor
};
#endif