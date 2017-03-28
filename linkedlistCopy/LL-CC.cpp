#include <iostream>
using namespace std;

/*Declare an implement the copy constructor for the LList class.*/

class LList {
public:
	LList() { head = 0; }
	void insert(int val) {// always add to the beginning, ignoring memory issues
		head = new Node(val, head);
	}
	void print() const {
		for (Node * cur = head; cur != 0; cur = cur->next) cout << cur->data << ", ";
		cout << endl;
		return;
	}
	bool removeLast(int val) {
		Node * current = head;
		Node * beforeFound = NULL;

		if (current != NULL && current->data == val) { // check for the first element
			beforeFound = head;
		}

		while (current != NULL) { //need to loop while items are in the list
			if (current->next != NULL && current->next->data == val) { // check if the next value is the desired value
				beforeFound = current;
			}
			current = current->next; // set current to the next node
		}

		if (beforeFound == NULL) // failure to find val
			return false;

		current = beforeFound->next;

		if (head == beforeFound) { // occurs if the first or second element needs to be removed
			if (current != NULL && current->data == val) { // check to see if it's the second element
				beforeFound->next = NULL;
				delete current;
			}
			else { //otherwise it must be the first element
				head = current;
			}
		}

		else { // node to be removed is in the middle
			beforeFound->next = current->next; // otherwise set the beforeFound node's next equal to the next next node
			delete current;
		}

		return true;
	}

private:
	struct Node {
		Node(int d, Node *n = 0) { data = d; next = n; }
		int data;
		Node *next;
	};
	Node * head;

	void copy(const LList & src) { 
		Node * current = src.head; // need to roam through the original list
		Node * copyHead = NULL; // need to make a copy head
		
		if (current != NULL) { // makes sure the list being copied isn't empty
			copyHead = new Node(current->data);
			current = current->next;
		}

		while (current != NULL) { // need to add items to the copy list while there are more
			Node * newNode = copyHead; 
			while (newNode->next != NULL) { // traverse the copy list until the end is reached
				newNode = newNode->next;
			}
			newNode->next = new Node(current->data); // add newest value to the end
		}
	}
};


void main() {
	LList list1;
	list1.insert(5);
	list1.insert(6);

	LList listCopy(list1);
	list1.print(); //should output 6 5
	listCopy.print(); //should output 6 5
	listCopy.insert(19);
	list1.insert(-5);
	cout << endl;
	listCopy.print(); //should print 19 6 5
	list1.print(); //should print -5 6 5
	cout << endl;
	LList listR;
	listR.insert(5);
	listR.insert(4);
	listR.insert(5);
	listR.insert(6);
	listR.insert(5);
	listR.print();
	cout << "removeLast(5) returned: " << listR.removeLast(5) << endl;
	listR.print();
	cout << "\nremoveLast(5) returned: " << listR.removeLast(5) << endl;
	listR.print();
	cout << "\nremoveLast(5) returned: " << listR.removeLast(5) << endl;
	listR.print();
	cout << "\nremoveLast(5) returned: " << listR.removeLast(5) << endl;
	listR.print();
	LList test;
	test.insert(1);
	cout << "\ntest remove with 1: " << test.removeLast(1) << endl;
	test.insert(2);
	test.print();
	test.insert(3);
	test.print();
	test.removeLast(2);
	test.print();
	test.insert(55);
	test.print();
	LList test1;
	test1.insert(1);
	test1.insert(2);
	test1.removeLast(1);
	test1.print();

}