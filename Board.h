
#ifndef BOARD_H
#define BOARD_H

#define ODDS 0
#define EVENS 1

#include <unordered_set>
#include <vector>
#include <string>
#include <tuple>
#include <mutex>

using namespace std;

class Board 
{
  public:
    Board();
    Board(vector<int> board);
    Board(string board);

    vector<int> getBoard();
    bool getTurn();
    bool getHasNegative();
    bool isOver();
    bool isTie();
    bool isWon();
    bool getWinner();
    int getNumOccupied();
    unordered_set<int> getAvailableOdds();
    unordered_set<int> getAvailableEvens();
    vector<Board> getPossibleMoves();
    Board getBestMove(bool player);
    bool validNextMove(Board other);
    
    int minimax(Board board, int depth, int alpha, int beta, bool isMaximizing);
    void calculateMinimax(vector<tuple<Board, int>> *results, mutex& mut, Board &board, int depth, bool player);

    void printBoard();
    void describe();

  private:

    vector<int> board;
    bool turn;
    bool over;
    bool won;
    bool winner;
    bool hasNegative;
    int numOccupied;
    unordered_set<int> availableOdds;
    unordered_set<int> availableEvens;

    vector<int> strToBoard(string board);
    void calculateTurn();
    void calculateRemaining();
    void calculateHasNegative();
    void calculateWon();
};

#endif