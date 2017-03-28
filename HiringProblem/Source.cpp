#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string> // added by me

using namespace std;

#define number_of_candidate 100

int candidate[number_of_candidate];

// populate the candidate array with random values based on the lower and higher bounds
void randomizeCandidates(int a, int b) {
	// Randomize the seed of random number
	srand(time(NULL));
	int r;
	for (int i = 0; i < number_of_candidate; i++)
	{
		r = rand() % (b - a + 1) + a;
		candidate[i] = r;
	}
	return;
}

// iterate through the candidates. finds the best candidate and increments count whenever a better candidate is found
void findBestCandidate(int &best, int &count) {
	for (int i = 0; i < number_of_candidate; i++)
	{
		if (candidate[i] > best)
		{
			best = candidate[i];
			count++;
			cout << "Current best is " << best << endl;
		}
	}
	return;
}

// prints the best and count
void printBest(int best, int count) {
	cout << "The best assistant is:" << best << endl;
	cout << "You hired " << count << " times." << endl;
	return;
}

// returns true if the char is a number
bool isNum(char ch) {
	if (ch >= 48 && ch <= 57)
		return true;
	return false;
}


// makes sure the user inputs valid numbers
void getInput(int &a, int &b) {
	string usrInput;
	bool flag = true;
	while (flag) {
		cout << "Please enter the lower bound: ";
		cin >> usrInput;
		flag = false;
		for (int i = 0; i < usrInput.length(); i++) {
			if (!isNum(usrInput[i])) {
				cout << "Please enter a valid number for the lower bound." << endl;
				flag = true;
				break;
			}
		}
	}
	a = stoi(usrInput);
	bool biggerFlag = true;
	while (biggerFlag) {
		flag = true;
		while (flag) {
			cout << "Please enter the upper bound: ";
			cin >> usrInput;
			flag = false;
			for (int i = 0; i < usrInput.length(); i++) {
				if (!isNum(usrInput[i])) {
					cout << "Please enter a valid number for the upper bound." << endl;
					flag = true;
					break;
				}
			}
		}
		b = stoi(usrInput);
		biggerFlag = false;
		if (b < a) {
			cout << "Enter a number greater than or equal to " << a << " for the upper bound." << endl;
			biggerFlag = true;
		}
	}
	return;
}





void main()
{
	int best = 0;
	int a, b;
	int count = 0;
	getInput(a, b);
	randomizeCandidates(a, b);
	findBestCandidate(best, count);
	printBest(count, best);

	system("pause");
}