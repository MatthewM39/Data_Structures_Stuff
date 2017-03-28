#include <iostream>
#include <ctime>
#include <string>
using namespace std;


// get four random numbers
void numGen(int &a, int &b, int &c, int &d) {
	a = rand() % 10;
	b = rand() % 10;
	c = rand() % 10;
	d = rand() % 10;
	return;
}

// makes sure the char is a number
bool isNum(char ch) {
	if (ch >= 48 && ch <= 57)
		return true;
	return false;
}

// check the number against the string
bool checkNum(int a, int b, int c, int d, string &str) {
	int first = (int)str[0] - 48; // convert the chars to int equivalents
	int second = (int)str[1] - 48;
	int third = (int)str[2] - 48;
	int fourth = (int)str[3] - 48;

	if (first == a) { // check all four letters for accuracy, if they're right then change that slot to A
		str[0] = 'A';
	}
	if (second == b) {
		str[1] = 'A';
	}
	if (third == c) {
		str[2] = 'A';
	}
	if (fourth == d) {
		str[3] = 'A';
	}
	if (str[0] != 'A') { // now check if any letter is mismatched, only for non "right" letters
		if (str[0] == b || str[0] == c || str[0] == d)
			str[0] = 'B';
	}
	if (str[1] != 'A') {
		if (str[1] == a || str[1] == c || str[1] == d)
			str[1] = 'B';
	}
	if (str[2] != 'A') {
		if (str[2] == b || str[2] == a || str[2] == d)
			str[2] = 'B';
	}
	if (str[3] != 'A') {
		if (str[3] == b || str[3] == c || str[3] == a)
			str[3] = 'B';
	}

	if (str == "AAAA") // string is all right, so return true :)
		return true;

	return false;
}

void runGame(int a, int b, int c, int d) {
	bool flag = true;
	while (flag) {
		string input;
		cout << "Enter a 4 digit number: ";
		cin >> input;
		if (input.length() == 4) {
			if (isNum(input[0]) && isNum((input[1])) && isNum(input[2]) && isNum(input[3])) {
							if (checkNum(a, b, c, d, input)) {
								cout << "Victory: " << a << b << c << d << endl;
								flag = false;
							}
							else {
								cout << input << endl;
								cout << "You're wrong" << endl;
							}

						}
		}
	}
}

int main() {
	srand(time(NULL)); // seeding rand with the time
	int a, b, c, d;
	while (true) {
		numGen(a, b, c, d);
		runGame(a, b, c, d);
	}
}