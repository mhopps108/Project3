//
//  TicTacToeBoard.cpp
//  Project3
//
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include <iostream>
using namespace std;

//
TicTacToeBoard::TicTacToeBoard() : GameBoard() {}

// destructor
//TicTacToeBoard::~TicTacToeBoard() {}

//
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
   if (list->empty()) {
      
   }
}

//
void TicTacToeBoard::ApplyMove(GameMove *move) {
   cout << "apply move" << endl;
   
   TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move);
   if (m == nullptr)
      throw TicTacToeException("Tried to apply a non-TicTacToeMove.");
   
   mBoard[m->mRow][m->mCol] = GetNextPlayer();//mNextPlayer;
   mValue = mNextPlayer;
   
   mHistory.push_back(m);
   mNextPlayer *= -1;
}

//
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
   }
}


// returns char value of a winner after searching the board
char TicTacToeBoard::CheckWinner() const {
   char winner = 0;
   // check for vertical and horizontal wins
   for (int i = 0; i < TTT_BOARD_SIZE; i++) {
      if (mBoard[0][i] == mBoard[1][i] && mBoard[1][i] == mBoard[2][i]) {
         winner = mBoard[0][i];
      }
      if (mBoard[i][0] == mBoard[i][1] && mBoard[i][1] == mBoard[i][2]) {
         winner = mBoard[i][0];
      }
   }

   // check for cross wins
   if ((mBoard[0][0] == mBoard[1][1] && mBoard[1][1] == mBoard[2][2]) ||
       (mBoard[0][2] == mBoard[1][1] && mBoard[1][1] == mBoard[2][0])) {
      winner = mBoard[1][1];
   }

   return winner;
}
