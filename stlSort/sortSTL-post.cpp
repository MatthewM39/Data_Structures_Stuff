#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
	int id() const { return sid; }
	void setId(int s) { sid = s; }				//your code must never call this method
	void print() const { cout << sid << '(' << name << "), "; }
	void setName(const string &n) { name = n; }   //your code must never call this method
	string getName() const { return name; }
private:
	int sid;
	string name;
	char otherData[10000];
};

bool studPred(const Student left, const Student right) { // sort students by ID
	return (left.id() < right.id()); // return if left is less than right
}

bool studPredPtr(const Student *left, const Student *right) { // sort students by ID
	return (left->id() < right->id()); // return if left is less than right
}

bool studBackwardsNamePred(const Student *left, const Student *right) { // sort students by reverse alphabetical
	string tempLeft = left->getName();
	return (tempLeft.compare(right->getName()) > 0); // return if left is greater than right
}

void main() {
	const int backup[10] = { 2,5,0,9,7,4,3,1,8,6 };//constant array with data to sort
	const string names[10] = { "CJ", "F", "A", "JJ", "HZ", "E", "DD", "B", "IM", "G" };
	int n = 10;

	vector<int> vec;

	vec.insert(vec.begin(), backup, backup + 10); // add elements from backup to beginning of the vector

	cout << "\tunsorted vec print: ";
	for (int i = 0; i<10; i++) cout << vec[i] << ", ";

	sort(vec.begin(), vec.end()); // sort the vector from beginning to end

	cout << "\n\tsorted vec print: ";
	for (int i = 0; i<10; i++) cout << vec[i] << ", ";
	cout << endl << endl;

	Student sarray[10];
	for (int i = 0; i<10; i++) {
		sarray[i].setId(backup[i]);//initialize Student's ids from backup
		sarray[i].setName(names[i]);
	}

	cout << "Unsort Studs ";
	for (int i = 0; i<10; i++) sarray[i].print();

	sort(sarray, sarray + 10, studPred); // sort the sarray by student id

	cout << "\nSort Studs ";
	for (int i = 0; i<10; i++) sarray[i].print();
	cout << endl << endl;


	for (int i = 0; i<10; i++) sarray[i].setId(backup[i]);//reset Student's ids from backup

	Student *psarray[10]; // array of student pointers
	for (int i = 0; i < 10; i++)	psarray[i] = &sarray[i]; // initialize to sarray
	sort(psarray, psarray + 10, studPredPtr);
	cout << "sort pointer: ";
	for (int i = 0; i<10; i++) psarray[i]->print();
	cout << endl << endl;

	Student tempArray[10];
	for (int i = 0; i < 10; i++) {
		tempArray[i] = *psarray[i];
	}

	for (int i = 0; i < 10; i++) {
		sarray[i] = tempArray[i];
	}

	cout << "sort Studs: ";
	for (int i = 0; i<10; i++) sarray[i].print();
	cout << endl << endl;

	Student *psarrayN[10]; // array of student pointers
	for (int i = 0; i < 10; i++)	psarrayN[i] = &sarray[i]; 
	sort(psarrayN, psarrayN + 10, studBackwardsNamePred); // sort based on backwards name predicate

	cout <<"sort pointer: ";
	for (int i=0; i<10; i++) psarrayN[i]->print();
	cout <<endl<<endl;

}