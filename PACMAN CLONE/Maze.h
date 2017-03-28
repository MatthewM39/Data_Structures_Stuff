#ifndef MAZE
#define MAZE
#include "CConsole.h"
#include <fstream>
#include <String>
using std::string;

class Game;

class Maze {

public: // these methods are public b/c other classes need to access them
	Maze(CConsole * console, Game * myGame); // maze constructor. set myConsole to the passed pointer

	bool loadMaze(const string &fileName); // load the maze from a given file. increments pelletNumber for each pellet

	void display(); // display the given maze

	int getPlayerStartX() const; // get the player starting x coord

	int getPlayerStartY() const; // get the player starting y coord

	int getMonsterStartX() const; // get monster spawn x coord

	int getMonsterStartY() const; // get monster spawn y coord

	bool done(); // checks to see if pelletNumber is 0

	char getMazeValue(int x, int y) const; // get the char value at a specific point

	void clearMazePosition(int x, int y); // clear the maze at a position and decrement pelletNumber

	void displayActors() const; // display all the players and monsters!

	int getPelletNumber() const; // return the number of pellets

	void computeDistance(int myMaze[23][21], int sx, int sy); // compute the shortest distance to a point

	void computeDistance(int sx, int sy); // an overload of the above

	bool getNextCoordinate(int myMaze[23][21] , int &curX, int &curY); // move towards the target coord on a map

	bool getNextCoordinate(int &curX, int &curY); // an overload of the above

	int getMazeDist(int x, int y); // returns the distance from monster spawn in the maze

	bool betweenX(int x, int c1, int c2, char ch); // return true if a char is found between two coords in the x axis

	bool betweenY(int y, int c1, int c2, char ch);// return true if a char is found between two coords in y axis

private: // private because these are all variables no one else needs to meddle with
	CConsole * myConsole; // pointer to game's console
	Game * myGame; // game pointer
	char myDisplay[23][21]; // 2D char array to hold the maze
	int maze[23][21]; // hold the distance map
	int pelletNumber; // number of pellets
	int playerStartX, playerStartY, monsterStartX, monsterStartY; // starting positions
};
#endif