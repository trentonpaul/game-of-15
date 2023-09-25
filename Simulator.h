
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Board.h"

class Simulator
{
  public:
    Simulator(Board board);
    void play(int count);
    int getTeamScore(bool team);
  private:
    Board board;
    int oddWins;
    int ties;
    int evenWins;
};

#endif