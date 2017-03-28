#include "Game.h"
#include "CConsole.h"
#include "Actor.h"
#include "Maze.h"
#include "Player.h"
#include "Monster.h"
#include "Inky.h"
#include "Clyde.h"
#include "Dinky.h"
#include "Stinky.h"
#include <iostream>

Game::Game(int ticks){
	myConsole = new CConsole(x, y); // create the cconsole
	myConsole->setColor(white, black); // default colors
	delay = ticks; // set the delay
}

Game::~Game(){
	delete myConsole; // delete myConsole
	delete myPlayer; // delete myPlayer
	delete myMaze; // delete myMaze
	delete myInky;
	delete myDinky;
	delete myClyde;
	delete myStinky;
}

void Game::run() {
	myMaze = new Maze(myConsole, this); // pass the maze pointers to the console and this game
	sprintf_s(fileName, 14, "MAZE%d.txt", level); // to load the files
	myMaze->loadMaze(fileName); // load the maze for the first time
	myPlayer = new Player(this, myMaze->getPlayerStartX(), myMaze->getPlayerStartY()); // create the player
	while (myMaze->loadMaze(fileName) && myPlayer->getLives() > 0 ) { // game needs to run while there are more mazes and the player has lives
			initializeActors(this); // create new instances of the player and monsters
			resetDisplays();
			myMaze->display(); // display the maze
			myMaze->displayActors(); // display the actors
			displayInfo(); // display lives, score, etc
			myConsole->printString(0, mazeY + 1, "Press enter to begin playing PacMan."); 
			myConsole->waitForEnter(); // wait til the player hits enter
			myConsole->printStringClearLine(0,mazeY + 1,""); // clear the press to enter line

			while (!myMaze->done() && myPlayer->getLives() > 0) { // while the player has lives and the maze isnt done a level is going
				movePlayer(); // move the player
				playerMonsterCollision();
				for (int i = 0; i < 4; i++) { // move monsters
					int tempX = myMonsters[i]->getX();
					int tempY = myMonsters[i]->getY();
					myConsole->printChar(tempX, tempY, myMaze->getMazeValue(tempX, tempY)); // clear char under a monster
					if (myMonsters[i]->getState() == Vulnerable) 
						myMonsters[i]->decTicks(); // for vulnerable monsters, decrease their ticks by 1
					myMonsters[i]->move(); // finally move the monster
				}
				playerMonsterCollision(); // test collision
				myMaze->displayActors();// display the actors
				displayInfo(); // update the info
				myConsole->delay(delay); // delay the game
			}

			if (myPlayer->getLives() > 0) { // make sure the player didnt lose
				level++;
				sprintf_s(fileName, 14, "MAZE%d.txt", level);
			
			}
	}

	if (myPlayer->getLives() > 0) { // make sure the player has lives
		myConsole->printString(0, mazeY + 1, "You won! Press enter to exit the game."); // player must've won
		myConsole->waitForEnter();
	}
}

int Game::getLevel() const{
	return level;
}

int Game::getPlayerX() const{
	return myPlayer->getX();
}

int Game::getPlayerY() const {
	return myPlayer->getY();
}

void Game::killPlayer(){
	myPlayer->decreaseLives(); // decrease lives

	if(myPlayer->getLives() > 0) // check if more lives
		myConsole->printString(0, mazeY + 1, "You died but have more lives! Press Enter to continue.");

	else // no more lives :c
		myConsole->printString(0, mazeY + 1, "You have lost all of your lives. Press Enter to quit.");

	myConsole->waitForEnter(); // either way, have to wait for user to press enter
	myConsole->printStringClearLine(0, mazeY + 1, ""); // clear the line

	if(myPlayer->getLives() > 0) // if the player has more lives, need to reset the actors to spawn
		resetDisplays();
}

void Game::makeMonstersVulnerable(){
	for (int i = 0; i < 4; i++) {
		State temp = myMonsters[i]->getState(); // get the monster's temp
		if (temp == Normal || temp == Vulnerable) { // doesn't affect dead monsters
			myMonsters[i]->setState(Vulnerable); // set to vulnerable
			myMonsters[i]->setColor(myMonsters[i]->getColor(), Color::green); // change bg to green
			if (level <= 8) // level less than 8, high amount of ticks
				myMonsters[i]->setTicks(100 - (level * 10));
			else // otherwise 20 ticks
				myMonsters[i]->setTicks(20);
		}
	}
}

void Game::clearMazePosition(int x, int y){
	myMaze->clearMazePosition(x, y);
}

char Game::getMazeContents(int x, int y) const{
	return myMaze->getMazeValue(x,y);
}

void Game::displayInfo(){
	string info = "Lives: " + std::to_string(myPlayer->getLives()) + " Score: " + std::to_string(myPlayer->getScore()) + " Level: " + std::to_string(level);
		myConsole->printString(0, mazeY, info);
}

bool Game::getCharInput(char& temp){
	return myConsole->getInput(temp);
}

void Game::changeDisp(int x, int y, char ch){
	myConsole->printChar(x, y, ch);
}

void Game::changeColor(Color fg, Color bg){
	myConsole->setColor(fg, bg);
}

void Game::resetDisplays() {
	myConsole->printChar(myPlayer->getX(), myPlayer->getY(), myMaze->getMazeValue(myPlayer->getX(), myPlayer->getY())); // display the pellet if there is one under the actor
	myPlayer->setX(myMaze->getPlayerStartX()); // change player xPos to spawn
	myPlayer->setY(myMaze->getPlayerStartY()); // change player yPos to spawn
	int monstX = myMaze->getMonsterStartX();
	int monstY = myMaze->getMonsterStartY();
	for (int i = 0; i < 4; i++){ // loop through monsters
		myMonsters[i]->setX(monstX); // set coords to spawn
		myMonsters[i]->setY(monstY);
		myMonsters[i]->setState(Normal); // normal state
		myMonsters[i]->setTicks(0); // normal ticks
		myMonsters[i]->resetDir(); // normal direction
		myMonsters[i]->setColor(myMonsters[i]->getColor(), black); // reset color
		myConsole->printChar(myMonsters[i]->getX(), myMonsters[i]->getY(), myMaze->getMazeValue(myMonsters[i]->getX(), myMonsters[i]->getY()));
	}
	myDinky->setRun(); // Dinky no longer should run 
	myPlayer->resetDir(); // reset direction for player
	myMaze->displayActors(); // display the actors
}

void Game::movePlayer() {
	int tempX = myPlayer->getX(); // temp var for player's xPos
	int tempY = myPlayer->getY(); // temp var for player's yPos
	char tempCH = myMaze->getMazeValue(tempX, tempY); // temp var for the ch at a position in the maze
	myConsole->printChar(tempX, tempY, tempCH); // needs to print that char
	myPlayer->move(); // call move for the player
	tempX = myPlayer->getX(); // get the new xPos for player
	tempY = myPlayer->getY(); // and the new yPos
	tempCH = myMaze->getMazeValue(tempX, tempY); // get the maze value at the position

	if (tempCH == '*') { // found a super pellet
		myPlayer->increaseScore(100); // increase score by 100
		myMaze->clearMazePosition(tempX, tempY); // clear the pellet
		makeMonstersVulnerable(); // make the monsters vulnerable
	}
	else if (tempCH == '.') { // found a normal pellet
		myPlayer->increaseScore(10); // raise score
		myMaze->clearMazePosition(tempX, tempY); // clear the position
	}
	if (extraLife == false && myPlayer->getScore() > 10000) { // got a lot of score, give a life
		extraLife = true;
		myPlayer->incrementLife();
	}
}

void Game::playerMonsterCollision(){
	for (int i = 0; i < 4; i++) {
		if (myPlayer->getX() == myMonsters[i]->getX() && myPlayer->getY() == myMonsters[i]->getY()) { // find collision
			if (!godMode && myMonsters[i]->getState() == Normal) { // normal monster, kill player
				killPlayer();
				break;
			}
			else if ((State)myMonsters[i]->getState() == Vulnerable) { // vulnerable monster, kill monster
				myMonsters[i]->setState(Dead);
				myMonsters[i]->setColor(myMonsters[i]->getColor(), Color::brown); // reset color
				myPlayer->increaseScore(1000); // increase score
			}
		}
	}
}

void Game::initializeActors(Game * game){
	int monstX = myMaze->getMonsterStartX(); 
	int monstY = myMaze->getMonsterStartY();
	myInky = new Inky(game, monstX, monstY, myMaze);
	myClyde = new Clyde(game, monstX, monstY, myMaze);
	myDinky = new Dinky(game, monstX, monstY, myMaze);
	myStinky = new Stinky(game, monstX, monstY, myMaze);
	myMonsters[0] = myInky; // set monsters in the array
	myMonsters[1] = myClyde;
	myMonsters[2] = myDinky;
	myMonsters[3] = myStinky;
}

bool Game::checkMaze(int x, int y, int n, int d){ // for a given direction, ensure the next spot isn't a wall
	if (d == 0) // up
		if (myMaze->getMazeValue(x, y - n) != '#')
			return true;
	if (d == 1) // down
		if (myMaze->getMazeValue(x, y + n) != '#')
			return true;
	if (d == 2) // left
		if (myMaze->getMazeValue(x - n, y) != '#')
			return true;
	if (d == 3) // right
		if (myMaze->getMazeValue(x + n, y) != '#')
			return true;
	return false;
}

Monster * Game::getMonster(int index){ // return a pointer to a monster from the array
	return myMonsters[index];
}

void Game::cheatCodes(char ch) {

	// Prevents monsters from killing the player, very handy
	if (ch == 'g') {
		if (godMode)
			godMode = false;
		else
			godMode = true;
	}

	// raise score by 1000
	else if (ch == 's')
		myPlayer->increaseScore(1000);

	// add a life
	else if (ch == 'l')
		myPlayer->incrementLife();

	// kill the player
	else if (ch == 'k')
		killPlayer();

	// make the monsters vulnerable
	else if (ch == 'v')
		makeMonstersVulnerable();

	// pause until enter is pressed
	else if (ch == 'p')
		myConsole->waitForEnter();

}