#include <vector>
#include <list>
#include <iostream>
#include <string>
using namespace std;

class HashTable {
public:
	HashTable(int arraySize) {
		if (arraySize <= 11)
			size = 11;
		else if (arraySize <= 101)
			size = 101;
		else if (arraySize <= 503)
			size = 503;
		else if (arraySize <= 1009)
			size = 1009;
		else if (arraySize <= 5003)
			size = 5003;
		else if (arraySize <= 7717)
			size = 7717;
		else if (arraySize <= 12829)
			size = 12829;
		else if (arraySize <= 17929)
			size = 17929;
		else // assuming array only goes up to 51539
			size = 51539;
		myTable = new vector<string>[size]; // create a dynamic array of string vectors
	}  

	~HashTable() {
		delete[] myTable; // delete the dynamic array
	}  

	void insert(const string &val) {
		myTable[Hash(val)].emplace_back(val); // find myTable index with hash, add value to end of that vector
	}

	bool search(const string &val) const {
		int location = Hash(val); // find where val might be using the hash
		int size = myTable[location].size(); // get the size of that vector
		for (int i = 0; i < size; i++) {
			if (myTable[location][i] == val) // traverse vector until val is found
				return true;
		}
		return false;
	}

	bool remove(const string &val) {
		int location = Hash(val);
		int size = myTable[location].size();
		for (int i = 0; i < size; i++) {
			if (myTable[location][i] == val) { // attempt to find val
				myTable[location].erase(myTable[location].begin() + i); // erase val
				return true;
			}
		}
		return false;
	}

	bool empty() const {
		for (int i = 0; i < size; i++) { // loop through the vectors
			if (!myTable[i].empty()) // make sure they're not empty
				return false;
		}
		return true;
	}

private:
	vector<string> * myTable; // will be used to create a dynamic array of string vectors
	int Hash(string str) const {
		int myHash;
		int length = str.size() -1;
		myHash = str[0] * str[length / 2] * str[length] * (size * 10); // multiply first, middle, and last chars together  and size*10
		return myHash % size; // mod by size
	}
	int size; // number of slots in the table
};


void main() {
	HashTable myTable(10);
	cout << "Is empty(1): " << myTable.empty() << endl;
	cout << "Attempt to find corgi(0): " << myTable.search("corgi") << endl;
	cout << "Attempt to remove corgi(0): " << myTable.remove("corgi") << endl;
	myTable.insert("corgi");
	cout << "Corgi added, attempt to search for corgi(1): " << myTable.search("corgi") << endl;
	myTable.insert("apple");
	myTable.insert("corgisaurus");
	myTable.insert("bear");
	myTable.insert("cat");
	myTable.insert("a");
	myTable.insert("dinosaur");
	myTable.insert("fish");
	myTable.insert("gorilla");
	myTable.insert("a word");
	cout << "Added other words, attempting to search for corgi(1): " << myTable.search("corgi") << endl;
	cout << "Empty check(0): " << myTable.empty() << endl;
	cout << "Search for Dinosaur(0): " << myTable.search("Dinosaur") << endl;
	myTable.insert("another word");
	cout << "Test search for a(1): " << myTable.search("a") << endl;
	myTable.insert("aaaaa");
	myTable.insert("ababa");
	myTable.insert("acaca");
	cout << "Test search for aaaaa, ababa, acaca (111): " << myTable.search("aaaaa") << myTable.search("ababa") << myTable.search("acaca") << endl;
	cout << "Now remove all strings(1): " << myTable.remove("corgi") << myTable.remove("apple") << myTable.remove("corgisaurus") << myTable.remove("bear")
		<< myTable.remove("cat") << myTable.remove("a") << myTable.remove("dinosaur") << myTable.remove("fish") << myTable.remove("gorilla") <<
		myTable.remove("a word") << myTable.remove("another word") << myTable.remove("aaaaa") << myTable.remove("ababa") << myTable.remove("acaca") << endl;
	cout << "Search for corgi (0) and empty(1): " << myTable.search("corgi") << myTable.empty() << endl;
	myTable.insert("corgi");
	cout << "Added corgi back, empty(0) search for corgi (1): " << myTable.empty() << myTable.search("corgi") << endl;
}