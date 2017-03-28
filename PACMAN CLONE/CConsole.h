#pragma once
#include <string>
#include <conio.h>
#include <windows.h>

enum Color {
	black = 0, blue = FOREGROUND_BLUE, green = FOREGROUND_GREEN, red = FOREGROUND_RED,
	purple = FOREGROUND_BLUE + FOREGROUND_RED, cyan = FOREGROUND_BLUE + FOREGROUND_GREEN,
	brown = FOREGROUND_GREEN + FOREGROUND_RED, white = FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED
};

class CConsole {
public:
	CConsole(int width, int height);
	void clearScreen();
	void setColor(Color fore, Color back) { SetConsoleTextAttribute(m_hConsole, fore + (back << 4)); }
	bool getInput(char& ch);
	char waitForInput();
	void waitForEnter();// wait until the user presses ENTER
	void gotoXY(int x, int y); //moves cursor to position x (from left), y (from top)
							   //0,0 is upper left corner
	void printChar(int x, int y, char ch); //prints ch at x,y, moves cursor over 1 to right
	void printChar(char ch) { _putch(ch); } //prints ch where current cursor is, moves cursor over 1 to right
	void printString(int x, int y, const std::string& s);
	void printString(const std::string& s);
	void printStringClearLine(const std::string& s); //clears rest of line after string printed
	void printStringClearLine(int x, int y, const std::string& s);
	void printInt(int x, int y, int val); //print an integer value at x,y
	void printInt(int val); //print an integer value
	void delay(int amount) { Sleep(amount); }
private:
	HANDLE  m_hConsole;
	int     m_width;
	int     m_height;
};