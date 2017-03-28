#include <iostream>
using namespace std;

template <typename ItemType>
class BST {//unbalanced binary search tree, no duplicates allowed, templated
public:
	enum Direction  { left, right }; // which way did you come from?

	BST() { root = 0; }//empty tree


	bool empty() const { return (root == 0); } //return true iff no nodes

	bool insert(ItemType val) { //insert val into a correct spot, return false if duplicate or out of memory
		if (empty()) {//special case since root must change
			root = new Node(val);
			return (root != 0); //return true if root is not NULL, NULL if no memory
		}
		return insert(val, root);
	}


	bool search(ItemType val) const {	//return true iff val found in tree
		return search(val, root);
	}

	bool remove(ItemType val) { //remove val, return true iff val found in tree
		if (empty()) return false;//depending on your implementation of remove, this may not be needed
		return remove(val, root, root, left);
	}

	//print values in order separated by spaces
	void traverseInOrderPrint() const { traverseInOrderPrint(root); }

private:
	struct Node {//constructor provided for simplicity of insert
		Node(ItemType d) : data(d), lChild(0), rChild(0) {}
		ItemType data;
		Node *lChild, *rChild;
	};
	Node * root;

	//below are recursive helpers for public methods with the same name
	bool insert(ItemType val, Node* &cur) {//note pass by reference, this is critical
		if (cur == 0) {//fell off tree, so new Node goes here
			cur = new Node(val);//since this is pass by reference, parent's child pointer will be changed
			return (cur != 0);
		}
		if (cur->data == val)  return false;
		if (val < cur->data) return insert(val, cur->lChild);
		else				 return insert(val, cur->rChild);
	}

	bool search(ItemType val, Node *cur) const {
		if (cur == 0)			  return false;
		if (cur->data == val) return true;
		if (val < cur->data)  return search(val, cur->lChild);//val smaller so we go left
		else				  return search(val, cur->rChild);
	}

	void traverseInOrderPrint(Node *cur) const {
		if (cur == NULL)	return; // fell off tree 
		traverseInOrderPrint(cur->lChild); // print left child first
		cout << cur->data << " " ; // print current 
		traverseInOrderPrint(cur->rChild); // print right child
	}

	bool remove(ItemType val, Node *cur, Node *trailer, Direction d) {
		if (cur == 0)	return false; // fell off tree, failed to find
		if (cur->data == val) { // val found

			if (cur->lChild == 0 && cur->rChild == 0) { // just a leaf
				if (cur == root) 
					root = 0;
				delete cur; // no children, delete it 
				if (d == left) 
					trailer->lChild = 0;
				else
					trailer->rChild = 0;
			}	

			else if (cur->lChild == 0) { // no left child
				if (cur == root) // cur is root so just set root as the right child
					root = cur->rChild;
				else {
					if (d == left) // came from the left
						trailer->lChild = cur->rChild; // set trailer's new left child to cur's right child
					else // otherwise came from right
						trailer->rChild = cur->rChild; // mirror of above
				}
				delete cur;
			}

			else if(cur->rChild == 0){
				if (cur == root)
					root = cur->lChild;
				if (d == left)
					trailer->lChild = cur->lChild;
				else
					trailer->rChild = cur->lChild;
				delete cur;
			}

			else {
				Node * minFinder = cur->rChild; // start at right child
				Node * minTrailer = cur; 
				while (minFinder->lChild != 0) { // find the smallest leaf
					minTrailer = minFinder; // set the trailer
					minFinder = minFinder->lChild; // iterate the minFinder
				}
				cur->data = minFinder->data; // swap the data values
				delete minFinder; 
				minTrailer->lChild = 0; // set the trailer's left child to null since we deleted it...
			}
			return true;
		}
		if (val < cur->data)	return remove(val, cur->lChild, cur, left); // go left on a branch when cur larger than val
		return remove(val, cur->rChild, cur, right); // else go right
	}
};

void main() {
	BST<int> tree;//your test code would go here
	int arr[] = { 10, 5, 3, 4, 8, 9, 17, 14, 13, 25, 20, 29, 32 };
	for (int i = 0; i< 13; i++) tree.insert(arr[i]);
	tree.traverseInOrderPrint();//should get 3 4 5 8 9 10 13 14 17 20 25 29 32
								//now remove various nodes and make sure the resulting tree is correct
								//be sure to test removing nodes with 0, 1, and 2 children and the root special cases
	cout << endl << "Remove 999 should be 0: " << tree.remove(999) << endl;
	cout << "Remove 32 should be 1: " << tree.remove(32) << endl;
	cout << "Remove 3 should be 1: " << tree.remove(3) << endl;
	cout << "Remove 8 should be 1: " << tree.remove(8) << endl;
	tree.traverseInOrderPrint();
	cout << endl << "Remove 17 should be 1: " << tree.remove(17) << endl;
	tree.traverseInOrderPrint();
	cout << endl << "Remove 10 should be 1: " << tree.remove(10) << endl;
	tree.traverseInOrderPrint();
	cout << endl << "woo, nothing blew up" << endl;
	BST<int> tree2;
	cout << "Attempt to remove from empty tree: " << tree2.remove(1) << endl;
	tree2.insert(1);
	tree2.traverseInOrderPrint();
	tree2.remove(1);
	cout << endl <<  "NOW REMOVE 1 AND PRINT SHOULD BE EMPTY" << endl;
	tree2.traverseInOrderPrint();
	cout << endl;
	tree2.insert(1);
	tree2.insert(2);
	tree2.traverseInOrderPrint();
	cout << endl;
	tree2.remove(1);
	tree2.traverseInOrderPrint();
	tree2.insert(1);
	tree2.traverseInOrderPrint();
	tree2.remove(2);
	cout << endl;
	tree2.traverseInOrderPrint();
	cout << endl << "woo, nothing else blew up" << endl;
}