#ifndef output
#define output
#include <iostream>
#include "process.cpp"

void sendOut(int a, int b, int c, int d, string input) {
	if (process::checkNum(a, b, c, d, input)) {
		cout << a << b << c << d << endl;
	}
	else {
		cout << "You're wrong" << endl;
	}
}


#endif