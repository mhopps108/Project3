//
//  TicTacToeMove.cpp
//  Project3
//
#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include <sstream>
using namespace std;

TicTacToeMove::TicTacToeMove() : mRow(-1), mCol(-1) {}

TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col) {}


// public:

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

bool TicTacToeMove::Equals(const GameMove &other) const {
   const TicTacToeMove *tttm = dynamic_cast<const TicTacToeMove*>(&other);
   if (tttm == nullptr)
      throw TicTacToeException("Tried to retrieve a non-TicTacToeMove.");
   
   return (mRow == tttm->mRow && mCol == tttm->mCol);
}

TicTacToeMove::operator std::string() const {
   ostringstream oss;
   oss << "(" << mRow << "," << mCol << ")";
   return oss.str();
}
