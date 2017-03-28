template <typename ItemType>
class Stack {
public:
	Stack() { head = 0; } // set head to 0

	~Stack() {
		Node * cur = head;
		while (cur) { // delete all the nodes
			Node * toDelete = cur;
			cur = cur->next;
			delete toDelete;
		}
	}

	bool empty() const {
		if (head == NULL) // if head is null, stack is empty
			return true;
		return false;
	}

	bool top(ItemType &output) const {
		if (!empty()) { // check for empty stack
			output = head->data; // stack isn't empty, set output to head's data
			return true; // success
		}
		return false;
	}

	bool push(const ItemType &item) {
		Node * newGuy = new Node(item);
		if (!newGuy) // memory check
			return false;
		newGuy->next = head; // add to beginning of list
		head = newGuy; // set head to newGuy
		return true;
	}

	bool pop() {
		if (!empty()) { // empty check
			Node * toDelete = head; // need to delete head
			head = head->next; // set head to the next node
			delete toDelete; // delete old head
			return true;
		}
		return false;
	} 		
private:

	struct Node {
		Node(ItemType d, Node *n = 0) : data(d), next(n) {}
		ItemType data;
		Node *next;
	};
	Node * head;

};
