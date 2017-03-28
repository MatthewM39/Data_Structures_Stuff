//Implement the size and total methods of LList
#include <iostream>
using namespace std;

class LList {
public:
	LList() { head = 0; }
	void insert(int val) {// always add to the beginning, ignoring memory issues
		Node * newGuy = new Node;
		newGuy->data = val;
		newGuy->next = head;
		head = newGuy;
	}
	int size() { //returns number of Nodes in LList
		Node * cur = head;
		int counter = 0;
		while (cur != NULL) {
			counter++; //increment by 1
			cur = cur->next;
		}
		return counter;
	}
	int total() { //returns sum of all the integers in the LList
		Node * cur = head;
		int counter = 0;
		while (cur != NULL) {
			counter = counter + cur->data; // add int from the node to the counter
			cur = cur->next;
		}
		return counter;
	}
private:
	struct Node {

		int data;
		Node *next;
	};
	Node * head;
};


void main() {
	LList test;
	cout << test.size() << endl;  //should print 0 since there are 0 nodes (it is empty)
	cout << test.total() << endl;  //should print 0 since the sum of all the values (all none of them) is 0
	test.insert(5);
	test.insert(8);
	test.insert(23);
	test.insert(-6);
	cout << test.size() << endl;  //should print 4 since there are 4 nodes
	cout << test.total() << endl;  //should print 30 since 5 + 8 + 23 + -6 is 30
}