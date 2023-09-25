
#include "Board.h"
#include "Utils.h"
#include <string>
#include <algorithm>
#include <thread>
#include <future>
#include <mutex>

/* PUBLIC MEMBERS */

// extern tuple<Board, int> calculateMinimax(Board &board, int depth, bool player)
// {
//   int score = board.minimax(board, depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
//   cout << "Calculating on " << endl;
//   board.printBoard();
//   cout << "Score: " << score << endl;
//   // res = make_tuple(board, score);
//   return tuple<Board, int>(board, score);
// }

Board::Board()
{
  this->board = this->strToBoard("(0,0,0,0,0,0,0,0,0)");
  this->numOccupied = count_if(
    this->board.begin(),
    this->board.end(),
    [](int i) {return i != 0;}
  );
  this->calculateTurn();
  this->calculateRemaining();
  this->calculateHasNegative();
  this->calculateWon();
}

Board::Board(vector<int> board)
{
  this->board = board;
  this->numOccupied = count_if(
    this->board.begin(),
    this->board.end(),
    [](int i) {return i != 0;}
  );
  this->calculateTurn();
  this->calculateRemaining();
  this->calculateHasNegative();
  this->calculateWon();
}

Board::Board(string board)
{
  this->board = this->strToBoard(board);
  this->numOccupied = count_if(
    this->board.begin(),
    this->board.end(),
    [](int i) {return i != 0;}
  );
  this->calculateTurn();
  this->calculateRemaining();
  this->calculateHasNegative();
  this->calculateWon();
}

vector<int> Board::getBoard()
{
  return this->board;
}

bool Board::getTurn()
{
  return this->turn;
}

bool Board::getHasNegative()
{
  return this->hasNegative;
}

bool Board::isOver()
{
  return this->over;
}

bool Board::isTie()
{
  return this->over && !this->won;
}

bool Board::isWon()
{
  return this->won;
}

bool Board::getWinner()
{
  return this->winner;
}

int Board::getNumOccupied()
{
  return this->numOccupied;
}

unordered_set<int> Board::getAvailableOdds()
{
  return this->availableOdds;
}

unordered_set<int> Board::getAvailableEvens()
{
  return this->availableEvens;
}

vector<Board> Board::getPossibleMoves()
{
  vector<Board> possible;
  unordered_set<int> available = (this->turn == ODDS) ? availableOdds : availableEvens;
  for (int i = 0; i < this->board.size(); i++)
  {
    if (this->board[i] == 0)
    {
      for (int a : available)
      {
        vector<int> newBoard(this->board);
        newBoard[i] = a;
        possible.push_back(newBoard);
        if (this->hasNegative == false)
        {
          newBoard = vector<int>(this->board);
          newBoard[i] = -a;
          possible.push_back(newBoard);
        }
      }
    }
  }

  return possible;
}

Board Board::getBestMove(bool player)
{
  int bestScore = numeric_limits<int>::min();
  int depth;
  if (this->numOccupied == 0) depth = 5;
  else if (this->numOccupied == 1) depth = 8;
  else depth = 9;
  // cout << "DEPTH: " << depth << endl;
  Board bestMove = Board(vector<int>({0,0,0,0,0,0,0,0,0}));
  vector<Board> possibleMoves = this->getPossibleMoves();
  vector<thread> threads;
  vector<tuple<Board, int>>* results = new vector<tuple<Board, int>>();
  // cout << "Possible Size: " << possibleMoves.size() << endl;
  mutex mut;
  for (Board &possible : possibleMoves)
  {
    threads.push_back(thread(Board::calculateMinimax, this, ref(results), ref(mut), ref(possible), depth, player));
    // int score = minimax(possible, depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
    // if (score > bestScore)
    // {
    //   bestMove = possible;
    //   bestScore = score;
    // }
  }
  for (thread &t: threads)
  {
    if (t.joinable())
      t.join();
  }
  for (tuple<Board, int> tup : *results)
  {
    // cout << "Total Size: " << results->size() << endl;
    Board board = get<0>(tup);
    // board.printBoard();
    int score = get<1>(tup);
    // cout << "Score: " << score << endl << endl;
    if (score > bestScore)
    {
      bestMove = board;
      bestScore = score;
    }
  }

  delete results;
  return bestMove;
}


void Board::calculateMinimax(vector<tuple<Board, int>> *results, mutex& mut, Board &board, int depth, bool player)
{
  // mut.lock();
  // cout << "BOARD:" << endl;
  // board.printBoard();
  // cout << endl;
  int score = this->minimax(board, depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
  mut.lock();
  results->push_back(tuple<Board, int>(board, score));
  mut.unlock();
}

bool Board::validNextMove(Board other)
{
  vector<int> otherBoard = other.getBoard();
  int numChanges = 0;

  if (other.getTurn() == this->turn) // wrong turn
    return false;

  for (int i = 0; i < this->board.size(); i++)
  {
    // if new number
    if (this->board[i] != otherBoard[i])
    {
      numChanges++;

      if (this->board[i] != 0) // change to a non-zero spot (replacing move)
        return false;
      if (numChanges > 1) // more than one board change total
        return false;
      else if (this->hasNegative && otherBoard[i] < 0) // adding a negative to a board that already has a negative
        return false;
      else if (otherBoard[i] % 2 != 0 && this->availableOdds.count(otherBoard[i]) == 0) // adding an odd that's not available
        return false;
      else if (otherBoard[i] % 2 == 0 && this->availableEvens.count(otherBoard[i]) == 0) // adding an even that's not available
        return false;
      else if (otherBoard[i] % 2 == 0 && this->turn == ODDS)
        return false;
      else if (otherBoard[i] % 2 != 0 && this->turn == EVENS)
        return false;
    }
  }
  if (numChanges == 0) // if nothing changed
    return false;

  return true;
}

void Board::printBoard()
{
  for (int i = 0; i < this->board.size(); i++) {
    cout << this->board[i] << " ";
    if ((i+1) % 3 == 0) {
      cout << endl;
    }
  }
}

void Board::describe()
{
  cout << endl << "--- DESCRIBING BOARD ---" << endl;
  this->printBoard();
  cout << "State notation: ";
  printVector(this->board);
  cout << endl << "Current turn: " << ((this->turn == ODDS) ? "ODDS" : "EVENS") << endl;
  cout << "Game over: " << ((this->over == true) ? "YES" : "NO") << endl;
  cout << "Game tied: " << ((this->over == true && this->won == false) ? "YES" : "NO") << endl;
  cout << "Game won: " << ((this->won == true) ? "YES" : "NO") << endl;
  cout << "Game winner (if applicable): " << ((this->winner == ODDS) ? "ODDS" : "EVENS") << endl;
  cout << "Has negative: " << this->hasNegative << endl;
  cout << "Remaining evens: ";
  printSet(this->availableEvens);
  cout << endl << "Remaining odds: ";
  printSet(this->availableOdds);
  cout << endl << endl;
}

/* PRIVATE MEMBERS */

vector<int> Board::strToBoard(string board)
{

  board.erase(remove(board.begin(), board.end(), ' '), board.end());
  board = board.substr(1, board.length()-2);
  
  return vector<int>(split(board, ','));
}

void Board::calculateTurn()
{
  int numOdds = 0, numEvens = 0;
  for (int i : this->board)
  {
    if (i == 0) continue;
    if (abs(i) % 2 == 0)
      numEvens++;
    else
      numOdds++;
  }
  if (numEvens == numOdds)
    this->turn = ODDS;
  else
    this->turn = EVENS;
}

void Board::calculateRemaining()
{
  unordered_set<int> odds({1, 3, 5, 7, 9});
  for (int i : board)
  {
    int absVal = abs(i);
    if (absVal % 2 != 0 && odds.count(absVal) > 0)
      odds.erase(absVal);
  }
  unordered_set<int> evens({2, 4, 6, 8});
  for (int i : board)
  {
    int absVal = abs(i);
    if (absVal % 2 == 0 && evens.count(absVal) > 0)
      evens.erase(absVal);
  }
  this->availableOdds = odds;
  this->availableEvens = evens;
}

void Board::calculateHasNegative()
{
  for (int i : this->board)
  {
    if (i < 0) {
      this->hasNegative = true;
      return;
    }
  }
  this->hasNegative = false;
}

void Board::calculateWon()
{

  // game over if all tiles occupied
  this->over = numOccupied == 9;

  // check rows and columns
  for (int i = 0; i < 3; i++) {
    int sumRow = 0, sumCol = 0;
    bool fullLineRow = true, fullLineCol = true;
    for (int j = 0; j < 3; j++) {
      if (this->board[i*3 + j] == 0) {
        fullLineRow = false;
      }
      sumRow += this->board[i*3 + j];
      if (this->board[i + j*3] == 0) {
        fullLineCol = false;
      }
      sumCol += this->board[i + j*3];
    }
    if (sumRow == 15 && fullLineRow || sumCol == 15 && fullLineCol) {
      this->won = true;
      this->over = true;
      this->winner = !this->turn;
      return;
    }
  }
  // check diagonals
  int sum1 = 0, sum2 = 0;
  bool full1 = true, full2 = true;
  for (int i = 0; i < 3; i++) {
    if (this->board[i*3 + i] == 0) {
      full1 = false;
    }
    if (this->board[i*3 + 2 - i] == 0) {
      full2 = false;
    }
    sum1 += this->board[i*3 + i];
    sum2 += this->board[i*3 + 2 - i];
  }
  if (sum1 == 15 && full1 || sum2 == 15 && full2) {
    this->won = true;
    this->over = true;
    this->winner = !this->turn;
    return;
  }
  this->won = false;
}

int Board::minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer)
{
  if (depth == 0)
  {
    return 0;
  }
  else if (board.isOver() == true)
  {
    if (board.isTie() == true)
      return 0;
    else if (board.getWinner() == maximizingPlayer)
      return depth;
    else
      return -depth;
  }

  vector<Board> posssibleMoves = board.getPossibleMoves();

  if (maximizingPlayer == board.getTurn())
  {
    int maxEval = numeric_limits<int>::min();
    for(Board nextMove : posssibleMoves)
    {
      int eval = this->minimax(nextMove, depth - 1, alpha, beta, maximizingPlayer);
      maxEval = max(maxEval, eval);
      alpha = max(alpha, eval);
      if (beta <= alpha)
        break;
    }
    return maxEval;
  }
  else
  {
    int minEval = numeric_limits<int>::max();
    for(Board nextMove : posssibleMoves)
    {
      int eval = this->minimax(nextMove, depth - 1, alpha, beta, maximizingPlayer);
      minEval = min(minEval, eval);
      beta = min(beta, eval);
      if (beta <= alpha)
        break;
    }
    return minEval;
  }

  return 1;
}