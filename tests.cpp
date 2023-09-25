#include "Board.h"
#include "utils.h"
#include <iostream>
#include <algorithm>

int testCounter = 0;
int passed = 0;

void runTest(string name, bool assertion)
{
  testCounter++;
  cout << "TEST " << testCounter << ": " << name << ": " << ((assertion == true) ? "PASSED" : "FAILED") << endl;
  if (assertion == true)
  {
    passed++;
  }
}

bool isWon(Board board)
{
  return board.isWon();
}

int main(int argc, char* argv[]) {
  Board b1("(0, -1, 0, 2, 5, 0, 6, 9, 0)");
  
  // int passed = 0;
  
  // getHasNegative
  runTest("getHasNegative()", b1.getHasNegative() == true);

  // getAvailableOdds
  runTest("getAvailableOdds()", b1.getAvailableOdds() == unordered_set<int>({3, 7}));

  // getAvailableEvens
  runTest("getAvailableEvens()", b1.getAvailableEvens() == unordered_set<int>({4, 8}));

  // getTurn
  runTest("getTurn()", b1.getTurn() == EVENS);
  runTest("getTurn() init odds", (Board("(0, 0, 0, 0, 0, 0, 0, 0, 0)")).getTurn() == ODDS);
  runTest("getTurn()", (Board("(0, 1, 0, 0, 0, 0, 0, 0, 0)")).getTurn() == EVENS);

  // getWon
  runTest("getWon()", (Board("(0, 1, 0, 2, 5, 0, 6, 9, 0)")).isWon() == true);

  // getWinner
  runTest("getWinner()", (Board("(0, 1, 0, 2, 5, 0, 6, 9, 0)")).getWinner() == ODDS);
  runTest("getWinner()", (Board("(0, 0, 0, 5, 4, 6, 7, 0, 0)")).getWinner() == EVENS);

  // validNextMove
  // valid test
  runTest("validNextMove()", b1.validNextMove(Board("(0, -1, 4, 2, 5, 0, 6, 9, 0)")) == true);
  // valid test
  runTest("validNextMove()", b1.validNextMove(Board("(8, -1, 0, 2, 5, 0, 6, 9, 0)")) == true);
  // invalid test: replacing move
  runTest("validNextMove() replacing move", b1.validNextMove(Board("(0, -1, 0, 3, 5, 0, 6, 9, 0)")) == false);
  // invalid test: double move
  runTest("validNextMove() double move", b1.validNextMove(Board("(0, -1, 3, 2, 5, 7, 6, 9, 0)")) == false);
  // invalid test: double negative
  runTest("validNextMove() double negative", b1.validNextMove(Board("(0, -1, -3, 2, 5, 0, 6, 9, 0)")) == false);
  // invalid test: invalid odd
  runTest("validNextMove() invalid odd", b1.validNextMove(Board("(0, -1, 1, 2, 5, 0, 6, 9, 0)")) == false);
  // invalid test: invalid even
  runTest("validNextMove() invalid even", b1.validNextMove(Board("(0, -1, 2, 2, 5, 0, 6, 9, 0)")) == false);
  runTest("validNextMove()", Board("(8, 3, 0, 0, 0, 0, 0, 0, 0)").validNextMove(Board("(8, 3, 4, 0, 0, 0, 0, 0, 0)")) == false);

  cout << "TURN 1: " << Board("(8, 3, 0, 0, 0, 0, 0, 0, 0)").getTurn() << endl;
  cout << "TURN 2: " << Board("(8, 3, 4, 0, 0, 0, 0, 0, 0)").getTurn() << endl;


  cout << endl << "Passed " << passed << " out of " << testCounter << " tests" << endl;

  vector<Board> possibleMoves = Board("(0, 3, 0, 0, 0, 0, 0, 0 ,0)").getPossibleMoves();
  // cout << endl << "Possible: " << possibleMoves.size() << endl;
  // cout << "Winners: " << count_if(possibleMoves.begin(), possibleMoves.end(), isWon) << endl;
  for (Board b : possibleMoves)
  {
    b.printBoard();
    // if (b.isWon())
    // {
    //   b.describe();
    // }
  }

  // Board b2("(9, 4, 0, 0, 0, 0, 0, 0, 0)");
  // b2.describe();

  // Board bestMove = b2.getBestMove(ODDS);
  // cout << "Best move:" << endl;
  // bestMove.describe();
}