
#include <iostream>
#include <vector>

#include "Board.h"
#include "Simulator.h"
#include "utils.h"

using namespace std;

int main(int argc, char*argv[]) {
  vector<Board> possibleBoards = Board("(0,0,0,0,0,0,0,0,0)").getPossibleMoves();
  int c = 0;
  for (Board b : possibleBoards)
  {
    if (c > 2) break;
    cout << "Analyzing board: " << vecToStr(b.getBoard()) << endl;
    Simulator sim(b);
    sim.play(1);
    cout << "Evens Score: " << sim.getTeamScore(EVENS) << endl;
    cout << "Odds Score: " << sim.getTeamScore(ODDS) << endl << endl;
  }
}