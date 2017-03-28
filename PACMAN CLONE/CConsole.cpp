#include "CConsole.h"

void CConsole::waitForEnter() {// wait until the user presses ENTER
  int ch;
  do {
	ch = _getch();
  } while ( ch != '\n'  &&  ch != '\r');
}

/* The getInput function checks whether the user has hit a key and immediately
 returns (so it does NOT wait for a key to be pressed).  It returns:
    true if the user has hit a key; in this case, the ch variable is set to
          the typed character 
    false if the user has not hit any key; in this case, the ch variable
          will be unchanged*/
bool CConsole::getInput(char& ch) {
  if (_kbhit()) {//has key been hit?
    int c = _getch();
    if (c != 0xE0)  // first of the two sent by arrow keys, E0 is escape
        ch = c;
    else {
      c = _getch(); //get second char sent by escape sequence from arrows
      switch (c) {
        case 'K':  /* left  */ ch = '4'; break;
        case 'M':  /* right */ ch = '6'; break;
        case 'H':  /* up    */ ch = '8'; break;
        case 'P':  /* down  */ ch = '2'; break;
        default:               ch = '?'; break;//special character but not arrow
      }
    }
    return true;
  }
  return false;
}

char CConsole::waitForInput() {
	char ch;
	while (!getInput(ch)) ;
	return ch;
}

CConsole::CConsole(int width, int height) : m_width(width), m_height(height) {
  m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO x;
  GetConsoleCursorInfo(m_hConsole, &x);
  x.bVisible=false;
  SetConsoleCursorInfo(m_hConsole, &x);//hides the cursor
}

void CConsole::gotoXY(int x, int y) {//moves cursor to position x (from left), y (from top)
//0,0 is upper left corner
  if (x < 0  ||  x >= m_width  ||  y < 0  ||  y >= m_height)	//invalid x,y
      return;
  COORD pos = { x, y };//same as pos.X=x; pos.Y=y;
  SetConsoleCursorPosition(m_hConsole, pos);
}

void CConsole::printChar(int x, int y, char ch) {//prints ch at x,y, moves cursor over 1 to right
  gotoXY(x,y);
  printChar(ch);
}

void CConsole::printString(int x, int y, const std::string& s) {
  gotoXY(x,y);
  printString(s);
}

void CConsole::printString(const std::string& s) {
  for (size_t i = 0; i < s.length(); i++)
      printChar(s[i]);
}

void CConsole::printStringClearLine(int x, int y, const std::string& s) {//clears rest of line after string printed
  gotoXY(x,y);
  printStringClearLine(s);
}

void CConsole::printStringClearLine(const std::string& s) {//clears rest of line after string printed
  printString(s);
  CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo(m_hConsole,&info);
  for (int col=info.dwCursorPosition.X; col < m_width; col++)
 	  printChar(' ');//print spaces for rest of line, console b/c don't know if we started at 0
}

void CConsole::printInt(int x, int y, int val) {//print an integer value
  gotoXY(x,y);
  printInt(val);
}
void CConsole::printInt(int val) {//print an integer value
  char buf[12]={0};
  _itoa_s(val, buf, 11, 10);//safely convert int to ascii text
  printString(buf);  //constructor for string automatically called for char *
}
void CConsole::clearScreen() {
  for (int i=0; i< m_height; i++) printStringClearLine(0,i,"");
}
