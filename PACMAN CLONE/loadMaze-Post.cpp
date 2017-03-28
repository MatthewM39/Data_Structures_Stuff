#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#include "CConsole.h"

class Maze {
public:
	Maze() {
		console = new CConsole(64, 24); 
	}

	~Maze() {
		delete console;
	}

	void display() const {
		for (int i = 0; i < xSize; i++) { 
			for (int j = 0; j < ySize; j++) {
				if (myDisplay[i][j] == '#' || myDisplay[i][j] == '*' || myDisplay[i][j] == '.') // if a wall char is found, need to print it
					console->printChar(i, j, myDisplay[i][j]);
			}
		}
	}

	void displayActors() const {
					console->setColor(black, red); // drawing the player, need to change colors
					console->printChar(playerX, playerY, '@'); // draw the player

					console->setColor(blue, white); // change colors
					console->printChar(monsterX, monsterY, 'M'); // draw the monster

					console->setColor(white, black); // swap back to default colors for now (this might be unecessary later in the project)
	}
 
	bool loadMaze(const string &filename) {
		ifstream input;
		input.open(filename); // attempt to open the file
		if (!input.is_open()) // make sure the file opens
			return false;
		string myString;
		int i = 0;
		while (i < ySize) { // go through the file until the maze height is reached
			getline(input, myString); // get the line as a string
			for (int j = 0; j < xSize; j++) { // convert to char array
				if (myString[j] == '@') { // if @ is found set player spawn coords
					playerX = j;
					playerY = i;
				}
				else if (myString[j] == '$') { // if $ is found set monster spawn coords
					monsterX = j;
					monsterY = i;
				}
				else
					myDisplay[j][i] = myString[j]; // otherwise, insert the char into the array
			}
			i++; 
		}
		return true;
	}




private:
  int playerX, playerY;
  int monsterX, monsterY;
  CConsole * console;
  static const int ySize = 21; // maze y dimension
  static const int xSize = 23; // maze x dimension
  char myDisplay[xSize][ySize]; // 2D char array to hold the maze
};  

void main () {
  Maze m;
  bool result = m.loadMaze("MAZE0.TXT"); 
  if (result) {
	  m.display();
	  m.displayActors();
  }
}
