#include <iostream>
#include "OrderedMultiList.h"
using namespace std;


OrderedMultiList::OrderedMultiList() {
	head = NULL; // constructor initially sets the head to be null
}

OrderedMultiList::~OrderedMultiList() {
	Node * toDestruct = head; // destructor node
	while (head) {
		toDestruct = head->next; // set the destructor node to head's next
		delete head; // delete head
		head = toDestruct; 
	}
}

bool OrderedMultiList::empty() {
	if (head == NULL) { // list is empty when head is null
		return true;
	}
	return false;
}

int OrderedMultiList::uniqueSize() {
	Node * cur = head;
	int counter = 0; // counter for unique size
	while (cur != NULL) {
		counter++; // increment on every node reached
		cur = cur->next;
	}
	return counter;
}

int OrderedMultiList::size() {
	Node * cur = head;
	int counter = 0;
	while (cur != NULL && cur->quantity > 0) {
		counter = counter + cur->quantity; // like uniqueSize, but counter is added to itself plus the current node's quantity 
		cur = cur->next;
	}
	return counter;
}

bool OrderedMultiList::find(char val) {
	Node * cur = head;
	while (cur != NULL && cur->ch != val) { // only go through while there are more nodes and val isn't reached
		cur = cur->next;
	}
	if (cur != NULL && cur->ch == val) { // value is successfully found
		return true;
	}
	return false;
}

int OrderedMultiList::count(char val) {
	Node * cur = head;
	while (cur != NULL && cur->ch != val) { // need to find the val
		cur = cur->next;
	}
	if (cur != NULL && cur->ch == val) { // if found return its quantity
		return cur->quantity;
	}
	return 0;
}

void OrderedMultiList::print() {
	Node * cur = head;
	while (cur != NULL) {
		cout << cur->quantity << " " << cur->ch << endl; // print this line for every node
		cur = cur->next;
	}
}


bool OrderedMultiList::insert(char val) {
	return insert(val, 1); // call the multi count insert...
}

bool OrderedMultiList::insert(char val, int count) {
	
	if (count < 1) { // count < 1 is invalid
		return false;
	}

	else if (!head) { // list is empty, must create the first node
		head = new Node(val, count);
		if (!head) {
			return false;
		}
	}

	else { // if head isn't NULL, must find the proper spot for val in the list
		Node * cur = head;
		Node * backOne = NULL;

		while (cur && cur->ch < val) { // loop while the end isn't reached and val is larger than the current node's ch values
			backOne = cur;
			cur = cur->next;
		}

		if (cur == NULL) { // end of the nodes, must create a new node
			Node * newNode = new Node(val, count);
			if (!newNode) {
				return false;
			}
			backOne->next = newNode; // set the previous node's next node to the newly created node
		}

		else if (cur->ch == val) { // if a node already contains val, add the quantity to val
			cur->quantity = cur->quantity + count;
		}

		else if (cur == head) { // must insert at beginning of the list
			Node * newNode = new Node(val, count);
			if (!newNode) {
				return false;
			}
			newNode->next = cur; // set the new node's next to the current head
			head = newNode; // change the head to be the new node
		}

		else{ // otherwise must be in the middle...
			Node * newNode = new Node(val, count);
			if (!newNode) {
				return false;
			}
			newNode->next = cur; 
			backOne->next = newNode;
		}
	}
	return true;
}

bool OrderedMultiList::remove(char val) {
	Node * cur = head;
	Node * backOne = NULL;
	while (cur != NULL && cur->ch != val) { // continue while the end isn't reached and val isn't found
		backOne = cur;
		cur = cur->next;
	}
	if (cur == NULL) { //unable to find val
		return false;
	}
	cur->quantity--; // success, so decrement quantity by 1
	if (cur->quantity > 0) { // if quantity > 0, then no need for anymore work
		return true;
	}
	removeNode(cur, backOne); // quantity is now below 0, must remove the node!
	
	return true;

}

int OrderedMultiList::removeAll(char val) {
	Node * cur = head;
	Node * backOne = NULL;
	while (cur != NULL && cur->ch != val) {
		backOne = cur;
		cur = cur->next;
	}
	if (cur == NULL) {
		return 0;
	}
	int amount = cur->quantity; // set the amount equal to the quantity which will be removed
	removeNode(cur, backOne); // remove the node!
	
	return amount; // return the amount
}

void OrderedMultiList::removeNode(Node * current, Node * previousNode) {

	if (head == current) { // if the node to be removed is the first, set head to current's next node
		head = current->next;
		delete current; // delete current node
	}
	else {
		previousNode->next = current->next; // else the previous node's next node is now current's next
		delete current; // current must be deleted
	}

}