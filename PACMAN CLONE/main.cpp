#include "Time.h"
#include "Game.h"

void main(int argc, char *argv[] ) {
  int delay=120;
  if (argc==2) delay=atoi(argv[1]);
  srand(static_cast<unsigned int>(time(0)));
  Game w(delay);
  w.run();
  return;
}