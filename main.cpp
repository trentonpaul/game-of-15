
#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <numeric>
#include <time.h>

#include "Board.h"
#include "Utils.h"

using namespace std;

Board randomOddStart()
{

  const vector<tuple<int, int>> options({
    tuple<int, int>(-1, 0),
    tuple<int, int>(-9, 1),
    tuple<int, int>(-7, 1), 
    tuple<int, int>(-3, 1), 
    tuple<int, int>(-1, 1),
    tuple<int, int>(-1, 2),
    tuple<int, int>(-9, 3),
    tuple<int, int>(-7, 3),
    tuple<int, int>(-3, 3),
    tuple<int, int>(-1, 3),
    tuple<int, int>(-1, 4),
    tuple<int, int>(-9, 5),
    tuple<int, int>(-7, 5),
    tuple<int, int>(-3, 5),
    tuple<int, int>(-1, 5),
    tuple<int, int>(-1, 6),
    tuple<int, int>(-9, 7),
    tuple<int, int>(-7, 7),
    tuple<int, int>(-3, 7),
    tuple<int, int>(-1, 7),
    tuple<int, int>(-1, 8)
  });

  srand ( time(NULL) );

  tuple<int, int> option = options[rand() % options.size()];
  int index = get<1>(option);
  int move = get<0>(option);

  vector<int> b({0, 0, 0, 0, 0, 0, 0, 0, 0});
  b[index] = move;
  return Board(b);
}

void getBoardNew(vector<int>& board) {
  
  int move = 0, index = 0;

  cout << "Enter the move: ";
  cin >> move >> index;

  board[index] = move;
}

int main(int argc, char*argv[]) {

  string boardInp;
  cout << "Enter the board, format: (a,b,d,e,f,g,h,i,j): ";
  getline(cin, boardInp);
  Board board = Board(boardInp);

  bool AITeam = board.getTurn();
  int turnNo = 1;

  cout << "AI playing as " << ((AITeam == EVENS) ? "EVENS" : "ODDS") << endl;

  /* TWO AIs FACING EACH OTHER */
  /*while (board.isOver() == false)
  {
    if (board.getTurn() == AITeam)
    {
      if (turnNo == 1 && AITeam == ODDS)
      {
        board = randomOddStart();
      }
      else
      {
        board = board.getBestMove(AITeam);
      }
      cout << "Turn: " << turnNo << " Current board:" << endl;
      board.printBoard();
    }
    else
    {
      board = board.getBestMove(board.getTurn());
      cout << "Turn: " << turnNo << " Current board:" << endl;
      board.printBoard();
    }
    turnNo++;
  }*/

  /* PLAYER VS. AI */
  while (board.isOver() == false)
  {
    if (board.getTurn() == AITeam)
    {
      if (turnNo == 1 && board.getNumOccupied() == 0 && AITeam == ODDS)
      {
        board = randomOddStart();
      }
      else
      {
      board = board.getBestMove(AITeam);
      }
      cout << "Current board:" << endl;
      board.printBoard();
      printVector(board.getBoard());
      cout << endl;
      cout << "Available moves: ";
      if (AITeam == ODDS)
        printSet(board.getAvailableEvens());
      else
        printSet(board.getAvailableOdds());
      cout << (!  board.getHasNegative() ? " (and negative!)" : "") << endl;
      // board.describe();
    }
    else
    {
      cout << "Enter your next move: ";
      getline(cin, boardInp);
      Board newBoard = Board(boardInp);
      if (!board.validNextMove(newBoard))
      {
        cout << "INVALID MOVE" << endl;
        return 0;
      }
      else
      {
        board = newBoard;
      }
    }
    turnNo++;
  }
  
  if (board.isTie())
  {
    cout << "Game tied" << endl;
  }
  else
  {
    cout << ((board.getWinner() == EVENS) ? "EVENS" : "ODDS") << " won the game!";
  }

}