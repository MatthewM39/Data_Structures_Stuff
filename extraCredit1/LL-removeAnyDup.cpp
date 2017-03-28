#include <iostream>
using namespace std;
//implement removeAny and removeDuplicates
//You are not allowed to change or create any other methods.


class LList {
public:
	LList() { head = 0; }
	void insert(int val) {// always add to the beginning, ignoring memory issues
		Node * newGuy = new Node;
		newGuy->data = val;
		newGuy->next = head;
		head = newGuy;
	}
	int removeAny(int val) {
		Node * cur = head;
		Node * backOne = NULL;
		Node * toDelete = NULL; // node to delete other nodes
		int counter = 0;

		while (cur) {
			if (cur->data == val) { // value is found
				toDelete = cur; // set the node to delete
				if (cur == head) { // first item is the value
					head = cur = cur->next; // change head and cur to cur->next				
					delete toDelete; // delete the item
					backOne = cur; // update backone
				}
				else {
					backOne->next = cur->next; // change the pointers
					cur = cur->next; // set cur equal to cur's next
				}
				delete toDelete; // delete the node with val
				counter++; // increment the counter
			} 
			else { // val isn't found, continue searching through the list
				backOne = cur;
				cur = cur->next;
			}
		}
		return counter;
	}
	
	int removeDuplicates() {
		Node * cur = head;
		Node * backOne = head;
		Node * toDelete = NULL;
		int counter = 0;

		while (cur) { 
			bool success = false; // value isn't succesfully found initially...
			Node * inner = cur->next; // inner node
			Node * innerBack = cur; // node before inner node
			while (inner) {
				if (inner->data == cur->data) { // inner data matches cur's
					success = true; // success flag to true
					toDelete = inner; // set the node to delete
					inner = inner->next; // set the inner node to the next node
					innerBack->next = inner;  // fix the trailing node
					delete toDelete; // delete the node
				}
				else { // failure to find the data, continue through the list
					innerBack = inner;
					inner = inner->next;
				}
			}
				
			if (success) { 
				counter++; // increment counter
				toDelete = cur; // need to delete node cur now
				if (cur == head) { 
					head = cur = cur->next;
					backOne = cur;
				}
				else {
					backOne->next = cur->next; // change the pointers
					cur = cur->next; // set cur equal to cur's next
				}
				delete toDelete;
			}
			else {
				backOne = cur;
				cur = cur->next;
			}
		}
		return counter;
	}	
	


	void print() const {
		for (Node * cur = head; cur; cur = cur->next) cout << cur->data << " ";
		cout << endl;
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
	int testValues[] = {11, 2, 3, 4, 5, 6, 7, 8 , 9, 0, 1};
	for (int i = 10; i >= 0; i--) test.insert(testValues[10 - i]);
	test.print();
	//test.removeAny(7);
	//test.removeAny(1);
	//test.removeAny(2);
	//test.removeAny(5);
	cout << endl << test.removeDuplicates() << endl;
	test.print();
}