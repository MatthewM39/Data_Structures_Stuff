#include "Actor.h"
#include "Game.h"

Actor::Actor(Game * game, int x, int y) {
	myGame = game; 
	xPos = x;
	yPos = y;
	myDirection = None; // actors start with no direction
}

int Actor::getX() const {
	return xPos;
}

int Actor::getY() const {
	return yPos;
}

Color Actor::getColor() const {
	return dColor;
}

Color Actor::getBgColor() const {
	return bgColor;
}

char Actor::getDisplayChar() const {
	return toDisplay;
}

Actor::Direction Actor::getDirection() const {
	return myDirection;
}

void Actor::setX(int x) {
	xPos = x;
}

void Actor::setY(int y) {
	yPos = y;
}

void Actor::setDisplayChar(char ch){
	toDisplay = ch;
}

void Actor::resetDir(){
	myDirection = None;
}

void Actor::move(){
	// does nothing. pure virtual
}

void Actor::setDirection(Direction d){
	myDirection = d;
}

void Actor::setColor(Color fg, Color bg) { // set foreground and background colors for actor
	dColor = fg;
	bgColor = bg;
}