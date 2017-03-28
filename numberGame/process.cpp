#ifndef process
#define process
#include <iostream>
using namespace std;


bool checkNum(int a, int b, int c, int d, string str) {
	int first = (int)str[0] - 48;
	int second = (int)str[1] - 48;
	int third = (int)str[2] - 48;
	int fourth = (int)str[3] - 48;
	if (first == a && second == b && third == c && fourth == d)
		return true;
	return false;
}

#endif