#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Graph {

public:
	Graph(){
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				myMatrix[i][j] = 0; // initialize to false and manually set to true for those connected
		myMatrix[0][4] = 1;		myMatrix[3][6] = 1;
		myMatrix[4][0] = 1;		myMatrix[6][3] = 1;
		myMatrix[4][2] = 1;		myMatrix[6][8] = 1;
		myMatrix[2][4] = 1;		myMatrix[8][6] = 1;
		myMatrix[4][7] = 1;		myMatrix[6][5] = 1;
		myMatrix[7][4] = 1;		myMatrix[5][6] = 1;
		myMatrix[2][1] = 1;		myMatrix[8][9] = 1;
		myMatrix[1][2] = 1;		myMatrix[9][8] = 1;
		myMatrix[7][2] = 1;		myMatrix[5][9] = 1;
		myMatrix[2][7] = 1;		myMatrix[9][5] = 1;
	}

	string findPath(int NodeA, int NodeB) {
		if (NodeA == NodeB)	return to_string(NodeA); // check if it's the same node first :)
		bool soFar[10] = { 0,0,0,0,0,0,0,0,0,0 }; // initialize an array of 10 booleans to false
		vector<int> currentNums; // create a vector for the current numbers
		currentNums.emplace_back(NodeA); // add the first node to the vector
		soFar[NodeA] = 1; // the first node has been used so flag it
		return findPath2(NodeA, NodeB, soFar, currentNums); // begin recursive calls
	}
	
	string findPath2(int NodeA, int NodeB, bool soFar[10], vector<int> currentNums) {
		if (myMatrix[NodeA][NodeB]) { // base case of two connected nodes
			str = "";
			vector<int>::iterator itr = currentNums.begin(); // iterate through current nums
			while (itr != currentNums.end()) {
				str = str + to_string(*itr) + " "; // add each current num in order to the string
				itr++;
			}
			str = str + to_string(NodeB); // add the last element
			return str;
		}
		for (int i = 0; i < 10; i++) { // otherwise, check the rest of the matrix
			if (soFar[i] == 0 && myMatrix[NodeA][i]) { // node can't be used before and must be connected to a
				soFar[i] = 1; // flag a node as used
				currentNums.emplace_back(i); // add it to current nums
				int tracker = currentNums.size(); // track the added items position in the vector
				if (findPath2(i, NodeB, soFar, currentNums) != "NONE")	return str; // recursive call, return the string only if a successful path is found
				soFar[i] = 0; // failure to find a path, so unflag the node
				currentNums.erase(currentNums.begin() + (tracker - 1)); // remove the node from the current nums
			}
		}
		return "NONE"; // overall failure
	}

private:
	bool myMatrix[10][10]; // true for X,Y if X is connected to Y
	string str; // concatenates the numbers
};

int main() {

	Graph myGraph;

	cout << "Testing 0's connection to other nodes" << endl;
	cout << myGraph.findPath(0, 0) << endl;
	cout << myGraph.findPath(0, 1) << endl; 
	cout << myGraph.findPath(0, 2) << endl;
	cout << myGraph.findPath(0, 3) << endl;
	cout << myGraph.findPath(0, 4) << endl;
	cout << myGraph.findPath(0, 5) << endl;
	cout << myGraph.findPath(0, 6) << endl;
	cout << myGraph.findPath(0, 7) << endl;
	cout << myGraph.findPath(0, 8) << endl;
	cout << myGraph.findPath(0, 9) << endl << endl;

	cout << "Testing 7's connection to other nodes" << endl;
	cout << myGraph.findPath(7, 0) << endl;
	cout << myGraph.findPath(7, 1) << endl;
	cout << myGraph.findPath(7, 2) << endl;
	cout << myGraph.findPath(7, 3) << endl;
	cout << myGraph.findPath(7, 4) << endl;
	cout << myGraph.findPath(7, 5) << endl;
	cout << myGraph.findPath(7, 6) << endl;
	cout << myGraph.findPath(7, 7) << endl;
	cout << myGraph.findPath(7, 8) << endl;
	cout << myGraph.findPath(7, 9) << endl << endl;

	cout << "Testing 6's connection to other nodes" << endl;
	cout << myGraph.findPath(6, 0) << endl;
	cout << myGraph.findPath(6, 1) << endl;
	cout << myGraph.findPath(6, 2) << endl;
	cout << myGraph.findPath(6, 3) << endl;
	cout << myGraph.findPath(6, 4) << endl;
	cout << myGraph.findPath(6, 5) << endl;
	cout << myGraph.findPath(6, 6) << endl;
	cout << myGraph.findPath(6, 7) << endl;
	cout << myGraph.findPath(6, 8) << endl;
	cout << myGraph.findPath(6, 9) << endl;
}