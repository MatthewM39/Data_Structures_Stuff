#include <iostream>
#include <string>
using namespace std;

template <typename ItemType>
class Circular {//doubly linked, circular, with dummy node

public:
	Circular() {
		dummy = new Node(); // make the dummy point to itself
		dummy->next = dummy;
		dummy->prev = dummy;

	}
	~Circular() {
		Node * destroyer = dummy->next; // go through the nodes
		while (destroyer != dummy) { // until dummy is reached
			destroyer = destroyer->next; // goto the next node
			delete destroyer->prev; // delete your previous node
		}
		delete dummy;
	}  
					
	Circular(const Circular &src) {
		dummy = new Node(); // set dummy up
		dummy->next = dummy;
		dummy->prev = dummy;
		Node *curSrc = src.dummy->next;
		while (curSrc != src.dummy) {
			insertLast(curSrc->data); // call insertLast with the source's value
			curSrc = curSrc->next; // goto the next node
		}
		
	}

	void insertFirst(const ItemType &val) {
		Node * temp = dummy->next; // create a temp node for dummy's current next
		dummy->next = new Node(val, temp, dummy); // set dummy's next as a new node with val
		temp->prev = dummy->next; // original's previous is now dummy's next
	}
	void insertLast(const ItemType &val) {//insert val so that it is the last item in list
		Node * temp = dummy->prev;
		dummy->prev = new Node(val, dummy, temp);
		temp->next = dummy->prev;
	}
	bool removeFirst(const ItemType &val) {//scan list and remove first val found, return true iff found

		Node * toRemove = dummy->next;
		while (toRemove != dummy) { // go through the list
			if (toRemove->data == val) { // value is found
				toRemove->prev->next = toRemove->next; // fix pointers
				toRemove->next->prev = toRemove->prev;
				delete toRemove; // delete the node
				return true;
			}
			toRemove = toRemove->next;
		}
		return false;
	}
	bool removeLast(const ItemType &val) {//scan list backwards and remove last val in list, return true iff found
		Node * toRemove = dummy->prev;
		while (toRemove != dummy) {
			if (toRemove->data == val) {
				toRemove->prev->next = toRemove->next;
				toRemove->next->prev = toRemove->prev;
				delete toRemove;
				return true;
			}
			toRemove = toRemove->prev;
		}
		return false;
	}
	bool search(const ItemType &val)const {//returns true iff val is in the list
		Node * cur = dummy->next;
		while (cur != dummy) {
			if (cur->data == val) // find the value
				return true;
			cur = cur->next;
		}
		return false;
	}
	void print() const {  //print out all values in linked list in order, items separated by spaces with endl after last
		Node * cur = dummy->next;
		while (cur != dummy) {
			cout << cur->data  << " "; // go through and print all the data
			cur = cur->next;
		}
		cout << endl;
	}
	void printR() const {  //print out all values in linked list in reverse order, items separated by spaces with endl after last
		Node * cur = dummy->prev;
		while (cur != dummy) {
			cout << cur->data << " "; // start at dummy's prev and work backwards to print in reverse
			cur = cur->prev;
		}
		cout << endl;
	}
private:
	struct Node {
		Node(){}
		Node(ItemType d, Node *n = 0, Node *p = 0) :data(d), next(n), prev(p) {}
		ItemType data;
		Node * next;
		Node * prev;
	};
	Node * dummy;
};

void main() {
	Circular<int> circ;
	int vals[] = { 1,20, 5, 4, 5, 3, 8, 5, 7 };
	for (int i = 0; i < 9; i++)
		circ.insertLast(vals[i]);
	circ.print();
	Circular<int> * other = new Circular<int>(circ);
	other->print();
	other->removeFirst(1);
	other->removeLast(7);
	other->print();
	other->printR();
	circ.insertLast(19);
	
	circ.print();  //should print 1 20 5 4 5 3 8 5 7 19
	circ.printR(); //should print 19 7 5 8 3 5 4 5 20 1
	circ.removeLast(5);
	cout << endl;
	circ.print();  //should print 1 20 5 4 5 3 8 7 19
	circ.printR(); //should print 19 7 8 3 5 4 5 20 1
	circ.removeFirst(5);
	cout << endl;
	circ.print();  //should print 1 20 4 5 3 8 7 19
	circ.printR(); //should print 19 7 8 3 5 4 20 1
	cout << endl;

	other->print();  //should print 20 5 4 5 3 8 5
	other->printR(); //should print 5 8 3 5 4 5 20
	delete other;
	cout << endl;

	Circular<string> words;
	words.insertFirst("hello");
	words.print();
}