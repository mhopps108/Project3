// Matt Hopps
// Project3
// TicTacToeMove.cpp
#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include <sstream>
using namespace std;

int TicTacToeMove::mOnHeap = 0;

// default constructor, assign -1,-1
TicTacToeMove::TicTacToeMove() : mRow(-1), mCol(-1) {}

// constructor with params
TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col) {}

// assignment operator
GameMove& TicTacToeMove::operator=(const std::string &str) {
   istringstream iss(str);
   char dummy;
   iss >> dummy >> mRow >> dummy >> mCol >> dummy;
   
   // throw exception if move is out of bounds
   if (mRow < 0 || mRow >= TTT_BOARD_SIZE ||
       mCol < 0 || mCol >= TTT_BOARD_SIZE) {
      throw TicTacToeException("Move is out of bounds.");
   }
   return *this;
}

// compare two TicTacToeMoves
bool TicTacToeMove::Equals(const GameMove &other) const {
   const TicTacToeMove *tttm = dynamic_cast<const TicTacToeMove*>(&other);
   if (tttm == nullptr)
      throw TicTacToeException("Tried to retrieve a non-TicTacToeMove.");
   
   return (mRow == tttm->mRow && mCol == tttm->mCol);
}

// returns string representation of a TicTacToeMove
TicTacToeMove::operator std::string() const {
   ostringstream oss;
   oss << "(" << mRow << "," << mCol << ")";
   return oss.str();
}
