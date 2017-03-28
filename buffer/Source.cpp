#include <stdio.h>
#include <iostream>

using namespace std;

void main() {
	char sample[11] = "SampleCode";
	char secret[18] = "this is my secret";
	char *p;
	p = sample;
	p -= 28;
	cout << p;
	cin.ignore();
}