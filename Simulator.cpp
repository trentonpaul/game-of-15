
#include <iostream>

#include "Simulator.h"

using namespace std;

Simulator::Simulator(Board board)
{
  this->board = board;
}

void Simulator::play(int count)
{
  this->oddWins = 0;
  this->ties = 0;
  this->evenWins = 0;

  for (int i = 0; i < count; i++)
  {
    cout << "Simulating " << (i+1) << " out of " << count << ":";
    Board gameBoard = this->board;

    while (gameBoard.isOver() == false)
    {
      gameBoard = gameBoard.getBestMove(gameBoard.getTurn());
    }
    if (gameBoard.isTie())
    {
      this->ties++;
      cout << " tie" << endl;
    }
    else if (gameBoard.getWinner() == EVENS)
    {
      this->evenWins++;
      cout << " even win" << endl;
    }
    else
    {
      this->oddWins++;
      cout << " odd win" << endl;
    }
  }
}

int Simulator::getTeamScore(bool team)
{
  if (team == EVENS)
  {
    return evenWins - oddWins;
  }
  else
  {
    return oddWins - evenWins;
  }
}