// Matt Hopps
//
// Project3
// OthelloView.cpp
#include "OthelloView.h"
using namespace std;

// prints the current OthelloBoard to ostream
void OthelloView::PrintBoard(ostream &s) const {
   s << "\n -   ";
   for (int n = 0; n < BOARD_SIZE; n++) {  // print top col numbers
      s << n << " ";
   }
   s << endl;
   for (int i = 0; i < BOARD_SIZE; i++) {  // loops through each spot putting..
      s << " " << i << " |";  // row numbers
      for (int j = 0; j < BOARD_SIZE; j++) {  // ..in black and white pieces
         if (mOthelloBoard->mBoard[i][j] == mOthelloBoard->BLACK) {
            s << " B";
         }
         else if (mOthelloBoard->mBoard[i][j] == mOthelloBoard->WHITE) {
            s << " W";
         }
         else {
            s << " .";
         }
      }
      s << " | " << endl;
   }
   s << endl;
}

// overloaded operator<< to print OthelloViews
//ostream& operator<< (ostream &lhs, const OthelloView &rhs) {
//   rhs.PrintBoard(lhs);
//   return lhs;
//}