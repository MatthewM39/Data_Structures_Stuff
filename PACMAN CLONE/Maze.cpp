#include "Maze.h"
#include "Game.h"
#include <stack>
#include "Monster.h"
#include <iostream>

using namespace std;

Maze::Maze(CConsole * console, Game * game) {
	myConsole = console;
	myGame = game;
} 

bool Maze::loadMaze(const string &fileName) {
	pelletNumber = 0;
	ifstream input;
	input.open(fileName); // attempt to open the file
	if (!input.is_open()) // make sure the file opens
		return false;
	string myString;
	int i = 0;
	while (i <mazeY) { // go through the file until the maze height is reached
		getline(input, myString); // get the line as a string
		for (int j = 0; j < mazeX; j++) { // convert to char array
			if (myString[j] == '@') { // if @ is found set player spawn coords
				playerStartX = j;
				playerStartY = i;
			}
			else if (myString[j] == '$') { // if $ is found set monster spawn coords
				monsterStartX = j;
				monsterStartY = i;
			}
			else{
				myDisplay[j][i] = myString[j]; // otherwise, insert the char into the array
				if (myString[j] == '.' || myString[j] == '*') // check for pellets!
					pelletNumber++; // increment pellets!
			}
		}
		i++;
	}
	computeDistance(monsterStartX, monsterStartY);
	input.close(); // close the file
	return true; // success, return true
}

void Maze::display(){
	for (int i = 0; i < mazeX; i++) {
		for (int j = 0; j < mazeY; j++) {
			if (myDisplay[i][j] == '#' || myDisplay[i][j] == '*' || myDisplay[i][j] == '.' || myDisplay[i][j] == '%' || myDisplay[i][j] == ' ') // check for display chars
				myConsole->printChar(i, j, myDisplay[i][j]); // display the display chars
		}
	}
}

int Maze::getPlayerStartX() const{
	return playerStartX;
}

int Maze::getPlayerStartY() const {
	return playerStartY;
}

int Maze::getMonsterStartX() const
{
	return monsterStartX;
}

int Maze::getMonsterStartY() const
{
	return monsterStartY;
}


bool Maze::done()
{
	if (pelletNumber < 1) // player ate all the pellets, so return true
		return true;
	return false;
}

char Maze::getMazeValue(int x, int y) const{
	return myDisplay[x][y];
}

void Maze::clearMazePosition(int x, int y){
	myDisplay[x][y] = ' '; // to clear a position, set it to be a space
	pelletNumber--; // decrease the pellet count
	myConsole->printChar(x, y, ' '); // print the new char
}

void Maze::displayActors() const
{
	myConsole->setColor(black, red); // drawing the player, need to change colors
	myConsole->printChar(myGame->getPlayerX(), myGame->getPlayerY(), '@'); // draw the player
	for (int i = 0; i < 4; i++) {
		Monster * tempM = myGame->getMonster(i);
		Color fg = red, bg = red;
		char toDisplay = tempM->getDisplayChar(fg, bg);
		if (tempM->getState() == Dead)
			toDisplay = '$';
		else if (tempM->getState() == Vulnerable)
			toDisplay = tolower(toDisplay);
		myConsole->setColor(fg, bg);
		myConsole->printChar(tempM->getX(), tempM->getY(), toDisplay);

	}
	myConsole->setColor(white, black); // swap back to default colors for now (this might be unecessary later in the project)
}

int Maze::getPelletNumber() const {
	return pelletNumber;
}

void Maze::computeDistance(int sx, int sy) {
	computeDistance(maze, sx, sy);
}

void Maze::computeDistance(int myMaze[23][21], int sx, int sy){
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 21; j++)
			myMaze[i][j] = 999;
	struct myPoint { int x; int y; }; // struct to hold cooords
	stack<myPoint> myStack; // stack of myPoints 
	myPoint refPoint, currentPoint; // variables for the reference point and the current point
	myMaze[sx][sy] = 0; // set the starting point to 0
	refPoint.x = sx; // set the reference points coords
	refPoint.y = sy;
	myStack.push(refPoint); // push it to the stack

	while (!myStack.empty()) { //while the stack isn't empty

		refPoint = myStack.top(); // set the  reference point equal to the top of the stack
		myStack.pop(); // pop it
		currentPoint = refPoint; // set the current point equal to each of the four adjacent points

								 // make sure the current point is a valid space to move, and a faster path hasn't been found
		if (myDisplay[refPoint.x + 1][refPoint.y] != '#' && myMaze[refPoint.x + 1][refPoint.y] > myMaze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x + 1; // handles the right coord
			currentPoint.y = refPoint.y;
			myMaze[refPoint.x + 1][refPoint.y] = myMaze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}

		if (myDisplay[refPoint.x - 1][refPoint.y] != '#' && myMaze[refPoint.x - 1][refPoint.y] > myMaze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x - 1; // left coord
			currentPoint.y = refPoint.y;
			myMaze[refPoint.x - 1][refPoint.y] = myMaze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}

		if (myDisplay[refPoint.x][refPoint.y + 1] != '#' && myMaze[refPoint.x][refPoint.y + 1] > myMaze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x;
			currentPoint.y = refPoint.y + 1; // up one coord
			myMaze[refPoint.x][refPoint.y + 1] = myMaze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}

		if (myDisplay[refPoint.x][refPoint.y - 1] != '#' && myMaze[refPoint.x][refPoint.y - 1] > myMaze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x;
			currentPoint.y = refPoint.y - 1; // down one coord
			myMaze[refPoint.x][refPoint.y - 1] = myMaze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}
	}
}

bool Maze::getNextCoordinate(int &curX, int &curY) {
	return getNextCoordinate(maze, curX, curY);
}

bool Maze::getNextCoordinate(int myMaze[23][21], int & curX, int & curY){
	if (myMaze[curX][curY] > myMaze[curX - 1][curY] && myMaze[curX - 1][curY] != '#')
		curX = curX - 1;
	else if (myMaze[curX][curY] > myMaze[curX + 1][curY] && myMaze[curX + 1][curY] != '#')
		curX = curX + 1;
	else if (myMaze[curX][curY] > myMaze[curX][curY + 1] && myMaze[curX][curY + 1] != '#')
		curY = curY + 1;
	else if (myMaze[curX][curY] > myMaze[curX][curY - 1] && myMaze[curX][curY - 1] != '#')
		curY = curY - 1;
	if (myMaze[curX][curY] == 0)
		return true;
	return false;
}

int Maze::getMazeDist(int x, int y) {
	return maze[x][y];
}

bool Maze::betweenX(int x, int c1, int c2, char ch){
	for (int i = 1; i < 11; i++)
		if (myDisplay[x][c1 + i] == '#')
			return true;
	return false;
}

bool Maze::betweenY(int y, int c1, int c2, char ch) {
	for (int i = 1; i < 11; i++)
		if (myDisplay[c1 + i][y] == '#')
			return true;
	return false;
}