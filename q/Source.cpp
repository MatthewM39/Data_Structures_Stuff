#include <iostream>
using namespace std;

template<class T>
class Queue {
private:
	struct Node {
		Node(T val, Node *n = NULL) : value(val), next(n){}
		T value;
		Node *next;
	};
	Node *myNode;
	int size;
public:
	Queue() {
		myNode = NULL;
		size = 0;
	}

	Queue(const Queue<T> &queue) {
		Queue *myQ = new Queue();
		Node * temp = queue->myNode;
		while (temp != NULL) {
			myQ->push(temp->myNode->value)
				temp = temp->next;
		}
		return myQ;
	}

	~Queue{
		while (myNode != NULL) {
			pop();
		}
	}

	int getLength() const {
		return size;
	}

	bool isEmpty() const {
		if (size == 0)
			return true;
	}
	void print() const {
		Node * temp = myHead;
		while (temp != NULL) {
			cout << temp->value << endl;
			temp = temp->next;
		}
	}

	bool push(const T &val) {
		Node *temp = myNode;
		Node *prev = myNode;
		while (temp != NULL) {
			myNode = temp;
			temp = temp->next;
		}
		prev->next = new Node(val, null);
	}

	T& first() {
		return myNode->value;
	}
	void pop() {
		Node * temp = myNode->next;
		T retVal = myNode->value;
		delete myNode;
		myNode = temp;
		return retVal;
	}
	bool operator==(const Queue<T> &queue) const {
		Node *temp = myNode;
		Node *temp2 = queue->myNode;
		while (myNode != NULL && temp2 != NULL) {
			if (temp->value != temp2->value)
				return false;
			temp = temp->next;
			temp2 = temp2->next;
		}
		if (temp != NULL || temp2 != NULL)
			return false;
		return true;
	}


};

