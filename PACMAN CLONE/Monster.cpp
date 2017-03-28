#include "Game.h"
#include "Monster.h"
#include <iostream>

Monster::Monster(Game * game, int x, int y, Maze * maze) : Actor(game, x, y){
	myState = Normal;
	vulnerableTicks = 0;
	int steps = 0;
	myMaze = maze;
}

State Monster::getState() const{
	return myState;
}

void Monster::setState(State state) {
	myState = state;
}

char Monster::getDisplayChar(Color & fg, Color & bg) const{ // returns FG  color, BG color, and the char 
	fg = getColor(); // via pass by reference
	bg = getBgColor();
	return Actor::getDisplayChar();  // normal return
}

void Monster::setTicks(int ticks){ // set ticks to a given value
	vulnerableTicks = ticks;
}

void Monster::decTicks() { // decrease ticks while > 0
	if (vulnerableTicks > 0) {
		vulnerableTicks--;
	}
	else {
		setState(Normal); // need to revert to normal
		setColor(getColor(), black);
	}
}

void Monster::move() {
}

void Monster::clearSteps() {
	steps = 0;
}