#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;

void main(char *args[]) {
	char program_to_run[12] = "testapp.exe";
	char buffer[] = "1234567890";
	char ptr[20], *head;
	head = buffer;
	cin >> ptr;
	for (int i = 0; i < strlen(ptr); i++, head++) {
		cout << *head;
		*head = ptr[i];
	}
	cout << endl;
	cout << program_to_run << endl;
	system(program_to_run);
	cin.ignore();
}