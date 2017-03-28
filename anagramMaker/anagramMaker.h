#ifndef ANAGRAMMAKER
#define ANAGRAMMAKER
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class AnagramMaker {

public: 
		struct wordInfo {
		char letterCount[26]; // counts the occurence of a letter in a word
		char myWord[31]; // store the word as a cstring
		char size;
		wordInfo(); //constructor
		};
		struct wordInfoTrimmed {
			char letterCount[26];
			int ind;
			char size;
		};
		struct wordInfoSuperTrimmed {
			char letterCount[26];
			char size;
		};
private:

	char countChars(char toCount[26], char myWord[31]); // store count of letters in a word

	bool loadWords(const std::string &dictionaryFile); // load the words from a file

	bool sizeComp(const char first[26], const  char second[26])const; // compare the size of two words

	unsigned int AnagramMaker::findAnagrams(list<int> &soFar, vector<wordInfoTrimmed> &currentDict, int pIt, char lettersLeft[26], int &size, int currentSize) const;

	unsigned int AnagramMaker::findAnagrams(vector<wordInfoSuperTrimmed> &currentDICT, int pIt, char lettersLeft[26], int &size, int currentSize) const;

	std::vector<wordInfo> myDictionaryVector; // a dictionary is loaded as a vector of wordInfos
	 
public:
	AnagramMaker(const std::string &dictionaryFile);
	unsigned int findAnagrams(const string &input, const bool &print) const;
};

#endif