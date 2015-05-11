// Matt Hopps
//
// Project3
// OthelloMove.cpp
#include "OthelloMove.h"
#include "OthelloBoard.h"
//#include "OthelloExceptions.h"
#include <sstream>
using namespace std;

//int OthelloMove::mOnHeap = 0;

// default constructor, assign -1,-1 a pass
OthelloMove::OthelloMove() : mRow(-1), mCol(-1) {}

// constructor with params
OthelloMove::OthelloMove(int row, int col) : mRow(row), mCol(col) {}

// assignment operator
GameMove& OthelloMove::operator=(const std::string &str) {
   if (str == "pass") {
      this->mRow = -1;
      this->mCol = -1;
   }
   else {
      istringstream iss(str);
      char dummy;
      iss >> dummy >> mRow >> dummy >> mCol >> dummy;
      // throw exception if move is out of bounds
      if (mRow < 0 || mRow >= BOARD_SIZE || mCol < 0 || mCol >= BOARD_SIZE) {
         throw OthelloException("Move is out of bounds.");
      }
   }
   return *this;
}

// operator==
bool OthelloMove::Equals(const GameMove &other) const {
   const OthelloMove *om = dynamic_cast<const OthelloMove*>(&other);
   if (om == nullptr)
      throw OthelloException("Tried to retrieve a non-OthelloMove.");
   
   return (mRow == om->mRow && mCol == om->mCol);
}

// returns string representation of a OthelloMove
OthelloMove::operator string() const {
   ostringstream oss;
   IsPass() ? oss << "pass" : oss << "(" << mRow << "," << mCol << ")";
   return oss.str();
}

