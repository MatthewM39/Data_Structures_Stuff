#include <iostream>
using namespace std;

class LList {
public:
	LList() :head(0), tail(0) {}  //same as head=tail=0;  same as head=tail=NULL;
	~LList() {//works for both #1 and #2
		Node * cur = head;
		while (cur) {
			cur = cur->next;
			delete head;
			head = cur;
		}
	}
	void insert(int val) {// always add to the end, ignoring memory issues, for #1
		if (!head) {
			head = new Node(val);	//empty list, new head
		}
		else {
			Node * cur = head;
			while (cur->next) cur = cur->next;
			cur->next = new Node(val);
		}
	}

	bool LList::remove(int val) {

		Node * current = head;
		Node * backOne = NULL; // extra node for going backwards

		while (current != NULL && current->data != val) { //need to loop while items are in the list and val isn't found
			backOne = current; // set the backOne node to current
			current = current->next; // set current to the next node
		}

		if (current == NULL)	return false; // failure to find the val

		if (head == current) { // if the first node contains val, make head point to the node after current
			head = current->next;
		}

		else if (current == NULL) { // if the last node contains val, the previous node's next needs to be NULL
			backOne->next == NULL;
		}

		else {
			backOne->next = current->next; // otherwise set the backOne node's next equal to current's next
		}

		delete current; // get rid of current
		return true;
	}



	void print() {
		Node * cur = head;
		while (cur != NULL) {
			cout << cur->data << " ";
			cur = cur->next;
		}
	}

private:
	struct Node {
		Node(int d, Node *n = 0, Node *p = 0) : data(d), next(n), prev(p) {}
		int data;
		Node *next, *prev;
	};
	Node * head, *tail;
};
