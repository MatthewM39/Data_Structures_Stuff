#ifndef GAME
#define GAME
#include "CConsole.h"

const int mazeY = 21;	// constants for maze size
const int mazeX = 23; 

const int x = 60;	// total cconsole size
const int y = 24;

class CConsole;
class Actor;
class Player;
class Maze;
class Monster;
class Clyde;
class Inky;
class Dinky;
class Stinky;

class Game {
public:

	Game(int ticks); // sets delay equal to the number of ticks

	~Game(); // free up memory

	void run(); // runs the game

	int getLevel() const; // return the current level number

	int getPlayerX() const; // return the player's x coord using myPlayer->getX()

	int getPlayerY() const; // return the player's y coord using myPlayer->getY()

	void killPlayer();  // decrease lives, reset actors

	void makeMonstersVulnerable(); // set monsters to vulnerable
	
	void clearMazePosition(int x, int y); // need to call the maze's clearMazePosition

	char getMazeContents(int x, int y) const; // get the value at a coordinate. use maze's getMazeValue

	void displayInfo(); // needs to display lives, level, and score at the bottom. access lives and score from myPlayer

	bool getCharInput(char& temp); // get the input char from the CConsole

	void changeDisp(int x, int y, char ch); // change the char displayed

	void changeColor(Color fg, Color bg); // change the CConsole's colors

	void resetDisplays(); // resets the actors

	void movePlayer(); // moves the player

	void playerMonsterCollision(); // detect collision

	void initializeActors(Game * game); // initialize the game actors

	bool checkMaze(int x, int y, int n, int d); // check the maze in a direction, x number of times

	Monster * getMonster(int index); // return a specific monster pointer from the array

	void cheatCodes(char ch); // cheats for testing

private:
	CConsole * myConsole; // pointer to game's console
	Maze * myMaze; // pointer to a maze
	int level = 0; // level counter
	char fileName[15]; // the filename
	int delay;
	bool godMode = false; // for testing
	bool extraLife = false; // player hasn't gotten an extra life yet
	Player * myPlayer; // player and monsters
	Inky * myInky;
	Dinky * myDinky;
	Stinky * myStinky;
	Clyde * myClyde;
	Monster *myMonsters[4]; // easy access for monsters
};
#endif 
