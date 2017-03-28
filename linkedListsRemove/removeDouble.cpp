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

	void insert(int val) {// always add to the end, ignoring memory issues, for #2
		if(!tail) {
			head=tail=new Node(val);	//new first element is both head and tail
		}
		else {
			tail->next=new Node(val, 0, tail);//new tail, its prev is old tail, no next
			tail=tail->next;
		}
	}

	//this prints the values in reverse starting with the last value, for #2 only
	void printReverse() const {

		Node * current = tail;
		while (current != NULL) {
			cout << current->data << " ";
			current = current->prev;
		}
		cout << endl;


	}

	bool remove(int val) {		//return true iff val was found
		Node * current = tail;
		while (current != NULL && current->data != val) { 
			current = current->prev; // navigate the list backwards until the end of the list or val is found
		}
		if (current == NULL) // return false when val not found
			return false;
		else if (current == head && tail == head) { // when there is only one item, set head and tail to NULL
			head = tail = NULL;
		}
		else if (current == head) { // if it's the first item
			head = current->next; // set head to the item after current
			current->next->prev = NULL; // set the item after current's prev to null
		}
		else if (current == tail) { // when the last item
			current->prev->next = NULL; // the previous item's next is null
			tail = current->prev; // the tail is now the previous item
		}
		else { // for removal in the middle
			current->prev->next = current->next; 
			current->next->prev = current->prev;
		}
		delete current; // get rid of the pointer
		return true; 
	}

private:
	struct Node {
		Node(int d, Node *n = 0, Node *p = 0) : data(d), next(n), prev(p) {}
		int data;
		Node *next, *prev;
	};
	Node * head, *tail;
};