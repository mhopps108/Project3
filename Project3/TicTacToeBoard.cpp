// Matt Hopps
// Project3
// TicTacToeBoard.cpp
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include <iostream>
using namespace std;

// constructor
TicTacToeBoard::TicTacToeBoard() : GameBoard() {
//   cout << "TicTacToe Constructor" << endl;
}

// adds all possible moves for the current player to list
void TicTacToeBoard::GetPossibleMoves(vector<GameMove *> *list) const {
   
   for (int row = 0; row < TTT_BOARD_SIZE; row++) {
      for (int col = 0; col < TTT_BOARD_SIZE; col++) {
         
         if (mBoard[row][col] == EMPTY) {
            TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(CreateMove());
            if (m == nullptr)
               throw TicTacToeException("Tried to create a non-TicTacToeMove.");
            m->mRow = row;
            m->mCol = col;
            list->push_back(m);
         }
      }
   }
}

// apply an TicTacToeMove to the TicTacToeBoard
void TicTacToeBoard::ApplyMove(GameMove *move) {
   TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move);
   if (m == nullptr)
      throw TicTacToeException("Tried to apply a non-TicTacToeMove.");
   
   mBoard[m->mRow][m->mCol] = GetNextPlayer();
   mHistory.push_back(m);
   
   mMoveCount++;  // increment boards move count
   mValue = (mMoveCount == MAX_MOVES ? EMPTY : GetNextPlayer());  // board value
   mNextPlayer *= -1;  // change to next player
}

// undo last TicTacToeMove in history vector
void TicTacToeBoard::UndoLastMove() {
   if (!mHistory.empty()) {
      TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(mHistory.back());
      if (m == nullptr)
         throw TicTacToeException("Tried to retrieve a non-TicTacToeMove.");
      
      mBoard[m->mRow][m->mCol] = EMPTY;
      delete m;
      mHistory.pop_back();
      
      mValue *= -1;
      mNextPlayer *= -1;
      mMoveCount--;
   }
}

// returns value of a winner after searching the board
int TicTacToeBoard::CheckWinner() const {
   int winner = EMPTY;
   // check for vertical then horizontal winners
   for (int i = 0; i < TTT_BOARD_SIZE; i++) {
      if (mBoard[0][i] == mBoard[1][i] && mBoard[1][i] == mBoard[2][i]) {
         if (mBoard[0][i] != EMPTY)
            winner = mBoard[0][i];
      }
      if (mBoard[i][0] == mBoard[i][1] && mBoard[i][1] == mBoard[i][2]) {
         if (mBoard[i][0] != EMPTY)
            winner = mBoard[i][0];
      }
   }

   // check for cross board winners
   if ((mBoard[0][0] == mBoard[1][1] && mBoard[1][1] == mBoard[2][2]) ||
       (mBoard[0][2] == mBoard[1][1] && mBoard[1][1] == mBoard[2][0])) {
      if (mBoard[1][1] != EMPTY)
         winner = mBoard[1][1];
   }
   return winner;
}
