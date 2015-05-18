// Matt Hopps
// Project3
// TicTacToeView.cpp
#include "TicTacToeView.h"
using namespace std;

// prints the current OthelloBoard to ostream
void TicTacToeView::PrintBoard(ostream &s) const {
   s << "\n    0  1  2 " << endl;
   s << "   ----------" << endl;
   for (int i = 0; i < TTT_BOARD_SIZE; i++) {
      s << " " << i << "|";
      for (int j = 0; j < TTT_BOARD_SIZE; j++) {
         if (mTicTacToeBoard->mBoard[i][j] == mTicTacToeBoard->X) {
            s << " X ";
         }
         else if (mTicTacToeBoard->mBoard[i][j] == mTicTacToeBoard->O) {
            s << " O ";
         }
         else {
            s << " . ";
         }
      }
      s << " | " << endl;
   }
   s << "   ----------" << endl;
}
