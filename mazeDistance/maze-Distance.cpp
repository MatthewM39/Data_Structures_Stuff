#include <iostream>
#include <stack>
using namespace std;

void computeDistance(int maze[][10], int sx, int sy) {
	struct myPoint { int x; int y; }; // struct to hold cooords
	stack<myPoint> myStack; // stack of myPoints 
	myPoint refPoint, currentPoint; // variables for the reference point and the current point
	maze[sx][sy] = 0; // set the starting point to 0
	refPoint.x = sx; // set the reference points coords
	refPoint.y = sy;
	myStack.push(refPoint); // push it to the stack

	while (!myStack.empty()) { //while the stack isn't empty

		refPoint = myStack.top(); // set the  reference point equal to the top of the stack
		myStack.pop(); // pop it
		currentPoint = refPoint; // set the current point equal to each of the four adjacent points

		// make sure the current point is a valid space to move, and a faster path hasn't been found
		if (maze[refPoint.x + 1][refPoint.y] != -1 && maze[refPoint.x + 1][refPoint.y] > maze[refPoint.x][refPoint.y]) { 
			currentPoint.x = refPoint.x + 1; // handles the right coord
			currentPoint.y = refPoint.y;
			maze[refPoint.x + 1][refPoint.y] = maze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}
		
		if (maze[refPoint.x - 1][refPoint.y] != -1 && maze[refPoint.x - 1][refPoint.y] > maze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x - 1; // left coord
			currentPoint.y = refPoint.y;
			maze[refPoint.x - 1][refPoint.y] = maze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}

		if (maze[refPoint.x][refPoint.y + 1] != -1 && maze[refPoint.x][refPoint.y + 1] > maze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x;
			currentPoint.y = refPoint.y + 1; // up one coord
			maze[refPoint.x][refPoint.y + 1] = maze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}

		if (maze[refPoint.x][refPoint.y - 1] != -1 && maze[refPoint.x][refPoint.y - 1] > maze[refPoint.x][refPoint.y]) {
			currentPoint.x = refPoint.x;
			currentPoint.y = refPoint.y - 1; // down one coord
			maze[refPoint.x][refPoint.y - 1] = maze[refPoint.x][refPoint.y] + 1;
			myStack.push(currentPoint);
		}
	}

}

void print(int maze[10][10]) {//neatly prints the maze
							  /*Walls are displayed as # signs.
							  Unreachable positions as spaces.
							  All other positions will have their distance printed. Since some distances
							  are >9 and wouldn't fit in a single digit, so print uses letters.  The
							  letter A represents 10, B is 11, C is 12, etc.*/

	for (int row = 0; row<10; row++) {
		for (int col = 0; col<10; col++) {
			if (maze[row][col] == -1) cout << "#";
			else if (maze[row][col] == 99) cout << ' ';
			else if (maze[row][col]>  9) cout << (char)(maze[row][col] - 10 + 'A');
			else cout << maze[row][col];
		}
		cout << endl;
	}
	cout << endl;
}

void main() {
	int maze[10][10] = {//-1 is a wall, 99 is empty, note border is all wall
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
		{ -1,99,99,99,99,99,99,99,99,-1 },
		{ -1,99,-1,-1,99,-1,-1,99,99,-1 },
		{ -1,99,-1,99,99,99,-1,99,99,-1 },
		{ -1,99,-1,-1,-1,99,-1,-1,99,-1 },
		{ -1,99,-1,99,99,99,-1,99,99,-1 },
		{ -1,99,99,99,-1,99,-1,99,99,-1 },
		{ -1,-1,-1,-1,-1,99,-1,-1,99,-1 },
		{ -1,99,99,99,99,99,99,99,99,-1 },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
	};
	print(maze);//starting maze, all 99 so just walls and spaces
	cout << endl;
	computeDistance(maze, 3, 3);//starting from 3,3
	print(maze);//should have distances in it now
}