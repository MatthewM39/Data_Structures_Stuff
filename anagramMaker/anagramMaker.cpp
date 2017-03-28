#include "anagramMaker.h"

AnagramMaker::AnagramMaker(const std::string &dictionaryFile) {
	loadWords(dictionaryFile);
}

bool wordPred(AnagramMaker::wordInfoTrimmed l, AnagramMaker::wordInfoTrimmed r) {  // > is big to small       < is small to big
	return l.size > r.size;
}

bool wordPredT(AnagramMaker::wordInfoSuperTrimmed l, AnagramMaker::wordInfoSuperTrimmed r) {
	return l.size > r.size;
}

unsigned int AnagramMaker::findAnagrams(const string &input, const bool &print) const {
	char stringLetterCount[26]; // take the input string
	char i;
	for (i = 0; i < 26; i++)	stringLetterCount[i] = 0;
	int len = input.length();
	std::vector<wordInfo>::const_iterator it = myDictionaryVector.begin();
	int ind = 0;
	for (i = 0; i < len; i++) {
		stringLetterCount[(input[i] - 'a')] += 1; // get the count of each letter in the input string and store it
	}
	int pIt = 0;
	int currentSize = len;
	if (print) { // if print, need to include indexs to words
		list<int> soFar; // list of ints soFar which will map to the index of a word in the dictionary
		vector<wordInfoTrimmed> myCurrentDict;
		while (it != myDictionaryVector.end()) {
			if (sizeComp(stringLetterCount, it->letterCount)) {
				wordInfoTrimmed newWord;
				newWord.ind = ind;
				newWord.size = it->size;
				for (i = 0; i < 26; i++) {
					newWord.letterCount[i] = it->letterCount[i];
				}
				myCurrentDict.emplace_back(newWord);
			}
			it++;
			ind++;
		}
		int size = myCurrentDict.size();
	

		sort(myCurrentDict.begin(), myCurrentDict.end(), wordPred);
		
		return  findAnagrams(soFar, myCurrentDict, pIt, stringLetterCount, size, currentSize); // begin recursive call
	}

	vector <wordInfoSuperTrimmed> myCurrentDict; // otherwise use the wordInfoSuperTrimmed without indexes and no need to pass soFar
	while (it != myDictionaryVector.end()) {
		if (sizeComp(stringLetterCount, it->letterCount)) {
			wordInfoSuperTrimmed newWord;
			for (i = 0; i < 26; i++) {
				newWord.letterCount[i] = it->letterCount[i];
			}
			newWord.size = it->size;
			myCurrentDict.emplace_back(newWord);
		}
		it++;
		ind++;
	}
	sort(myCurrentDict.begin(), myCurrentDict.end(), wordPredT);
	int size = myCurrentDict.size();
	
	return findAnagrams(myCurrentDict, pIt, stringLetterCount, size, currentSize); // begin recursive call
}

char AnagramMaker::countChars(char toCount[26], char myWord[31])  {
	char i = 0;
	while(myWord[i] != '\0' && i < 31) {
		toCount[myWord[i] - 'a'] += 1; // increment a letter's count when it is found
		i++;
	}
	return i;

}

bool AnagramMaker::loadWords(const std::string &dictionaryFile) {
	std::ifstream myStream(dictionaryFile);
	while (myStream) {
		wordInfo tempWord;
		myStream.getline(tempWord.myWord, 31, '\n'); // get a word
		tempWord.size = countChars(tempWord.letterCount, tempWord.myWord); // get it's character count
		myDictionaryVector.push_back(tempWord); // put the word in the dictionary
	}
	myDictionaryVector.pop_back(); // pop the empty element
	return true;
}

bool AnagramMaker::sizeComp(const char first[26], const char second[26]) const
{
	for (char i = 0; i < 26; i++) {
		if ((first[i] - second[i]) < 0)	return false; // if the second word has more of a letter, return false
	}
	return true;
}

unsigned int AnagramMaker::findAnagrams(list<int> &soFar, vector<wordInfoTrimmed> &currentDict, int pIt, char lettersLeft[26], int &size, int currentSize) const
{
	int count = 0;
	char result[26];
	char i;
	while (pIt != size) { // haven't reached end of the current dictionary yet
		if (sizeComp(lettersLeft, currentDict[pIt].letterCount)) { // compare letters remaining with next word
			for (i = 0; i < 26; i++) {
				result[i] = lettersLeft[i] - currentDict[pIt].letterCount[i]; // word is less so subtract it
			}
			
			currentSize = currentSize - (int) currentDict[pIt].size;
			if (currentSize == 0) { // see if we ran out of letters
				list<int>::iterator quickIt = soFar.begin();
				while (quickIt != soFar.end()) {
					cout << myDictionaryVector[currentDict[*quickIt].ind].myWord << " ";
					quickIt++;
				}
				cout << myDictionaryVector[currentDict[pIt].ind].myWord << endl;

				count++; // increment count
			}
			else {
				soFar.emplace_back(pIt); // otherwise, add current word to sofar
				count = count + findAnagrams(soFar, currentDict, pIt, result, size, currentSize); // recursive call
				soFar.pop_back(); // remove current word
			}
		}
		pIt++; // move to the next word in the dictionary
	}
	return count;
}

unsigned int AnagramMaker::findAnagrams(vector<wordInfoSuperTrimmed>& currentDict, int pIt, char lettersLeft[26], int & size, int currentSize) const
{
	int count = 0;
	char result[26];
	char i;
	while (pIt != size) { // haven't reached end of the current dictionary yet
		if (sizeComp(lettersLeft, currentDict[pIt].letterCount)) { // compare letters remaining with next word
			for (i = 0; i < 26; i++) {
				result[i] = lettersLeft[i] - currentDict[pIt].letterCount[i]; // word is less so subtract it
			}
			currentSize -=currentDict[pIt].size;
			if (currentSize == 0) { // see if we ran out of letters
				count++; // increment count
			}
			else {
				count = count + findAnagrams(currentDict, pIt, result, size, currentSize); // recursive call
			}
		}
		pIt++; // move to the next word in the dictionary
	}
	return count;
}

AnagramMaker::wordInfo::wordInfo() {
	for (char i = 0; i < 26; i++) {
		letterCount[i] = 0; // initialize the array to 0
	}
}