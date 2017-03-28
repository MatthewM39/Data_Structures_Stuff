// CODE FOR PERMUTATIONS
#include <iostream>
#include <string>
using namespace std;

int permutations2(string input, int index, int length) { // permutes a string back to front. 
	int x = 0; // counter variable
	if (index == 0) { // front reached, so done permuting 
		cout << input << endl;
		return 1; // increase the number of permutations by 1
	}
	else {
		for (int i = index; 0 <= i; i--) { // loop to beginning of string from current index
			char temp = input[i]; // switch the char at index with char index - i
			input[i] = input[index];
			input[index] = temp;
			x = x + permutations2(input, index - 1, length); // now permute again
			temp = input[i]; // swap back for the next iteration
			input[i] = input[index];
			input[index] = temp;
		}
	}
	return x; 
}

int permutations(string input) {
	return permutations2(input, input.size()  - 1, input.size()); // start at the last char. 
}



void main() {
	cout << permutations("abc") << endl; // 6
	cout << permutations("abcd") << endl; // 24
	cout << permutations("abcde") << endl; // 120
}

// END CODE FOR PERMUTATIONS