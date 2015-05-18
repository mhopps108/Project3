// Matt Hopps
// Project3
// OthelloBoard.cpp
#include "OthelloBoard.h"
#include "OthelloMove.h"
using namespace std;

// default constructor, initial board setup for new game
OthelloBoard::OthelloBoard() : GameBoard() {
//   cout << "OthelloBoard Constructor" << endl;
   int mid = BOARD_SIZE/2;
   mBoard[mid-1][mid] = BLACK;
   mBoard[mid][mid-1] = BLACK;
   mBoard[mid-1][mid-1] = WHITE;
   mBoard[mid][mid] = WHITE;
}

// adds all possible moves for the current player that result in points, or pass
void OthelloBoard::GetPossibleMoves(vector<GameMove *> *list) const {

   char opponent = mNextPlayer * -1;  // opposing player
   for (int row = 0; row < BOARD_SIZE; row++) {  // loop through every spot on
      for (int col = 0; col < BOARD_SIZE; col++) {  // on board
         
         bool moveFound = false;  // flag if a move is found, added to vector
         if (mBoard[row][col] == EMPTY) {  // check for empty spots
            for (int moveX = -1; moveX <= 1; moveX++) {
               for (int moveY = -1; moveY <= 1; moveY++) {
                  
                  if (!moveFound) {  // only add once for each possible move
                     int r = row + moveX;
                     int c = col + moveY;
                     
                     if (InBounds(r, c)) {
                        while (mBoard[r][c] == opponent) {
                           r += moveX;
                           c += moveY;
                           // check for current player piece that will enclose
                           // opponent making this a valid scoring move
                           if (InBounds(r, c)) {
                              if (mBoard[r][c] == mNextPlayer) {
                                 OthelloMove *m =
                                       dynamic_cast<OthelloMove*>(CreateMove());
                                 if (m == nullptr)
                                    throw OthelloException
                                         ("Tried to create a non-OthelloMove.");
                                 m->mRow = row;
                                 m->mCol = col;
                                 list->push_back(m);  // add move to vector
                                 moveFound = true; // found a move for this spot
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   // no moves found, only possible is a pass, add a pass
   if (list->empty()) {
      list->push_back(CreateMove()); // default OthelloMove constructor is pass
   }
}

// apply an OthelloMove to the OthelloBoard keeping track of FlipSets
void OthelloBoard::ApplyMove(GameMove *move) {

   OthelloMove *m = dynamic_cast<OthelloMove*>(move);
   if (m == nullptr)
      throw OthelloException("Tried to apply a non-OthelloMove.");
   
   char opponent = mNextPlayer * -1;  // opposing player
   if (m->IsPass()) {
      mPassCount++;  // pass, increment passCount
   }
   else {
      mBoard[m->mRow][m->mCol] = mNextPlayer;  // apply current move first
      mValue += mNextPlayer; // add new board piece to OthelloBoard value
      
      // loop through all possible directions from a given board piece, 9 total
      for (int moveX = -1; moveX <= 1; moveX++) {
         for (int moveY = -1; moveY <= 1; moveY++) {
            
            if (moveX == 0 && moveY == 0) {
               continue;  // skip 0 0 of loop because it wont go anywhere
            }
            int switched = 0;  // count of number of opponets pieces found
            int r = m->mRow + moveX;  // use temp row/col value to not change..
            int c = m->mCol + moveY;  // ..original after increments
            
            // add moveX/Y to row/col to look around the placed piece
            if (InBounds(r, c)) {
               while (mBoard[r][c] == opponent) {
                  switched++;  // found an opponets piece in current direction..
                  r += moveX;  // ..when other player piece is found continue to
                  c += moveY;  // ..move in that direction looping for another
                  
                  // check for current player piece that will enclose opponent
                  if (InBounds(r, c)) {
                     if (mBoard[r][c] == mNextPlayer) {
                        for (int i = 0; i < switched; i++) {
                           r -= moveX;  // start back tracking and changing..
                           c -= moveY;  // ..opponents found to currentPlayers
                           mBoard[r][c] = mNextPlayer;
                           // add switched pieces to OthelloBoard value
                           mValue += (2 * mNextPlayer);
                        }
                        mPassCount = 0;  // reset passCount
                        // add a FlipSet to this move
                        m->AddFlipSet(OthelloMove::
                                      FlipSet(switched, moveX, moveY));
                     }
                  }
               }
            }
         }
      }
   }
   mHistory.push_back(m);  // add OthelloMove to the history vector
   mNextPlayer = opponent;  // update next player
}

// undo last OthelloMove in history vector
void OthelloBoard::UndoLastMove() {
   if (!mHistory.empty()) {
      OthelloMove *m = dynamic_cast<OthelloMove*>(mHistory.back()); // last move
      if (m == nullptr)
         throw OthelloException("Tried to retrieve a non-OthelloMove.");
      
      if (m->IsPass()) {  // move was a pass, decrement passCount
         mPassCount -= 1;
      }
      else {
         mValue += mNextPlayer;  // undo last played piece from board value
         for (int i = 0; i < m->mFlips.size(); i++) {
            int r = m->mRow;
            int c = m->mCol;
            mBoard[r][c] = EMPTY;  // remove last played piece from board
            
            int moveX = m->mFlips[i].rowDelta;
            int moveY = m->mFlips[i].colDelta;
            // in delta direction switch back the number of pieces flipped
            for (int j = 0; j < m->mFlips[i].switched; j++) {
               mBoard[r += moveX][c += moveY] = mNextPlayer;  // flip piece
               mValue += (2 * mNextPlayer);  // undo board value
            }
         }
      }
      delete m;  // delete OthelloMove
      mHistory.pop_back();  // and remove from history vector
      mNextPlayer *= -1;  // change player
   }
}