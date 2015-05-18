// Matt Hopps
// Project3
// TicTacToeBoard.h
#ifndef __Project3__TicTacToeBoard__
#define __Project3__TicTacToeBoard__

#include "GameBoard.h"
#include "GameMove.h"
#include "TicTacToeMove.h"
#include <vector>
#include <iostream>

const int TTT_BOARD_SIZE = 3; // width and height of board
const int MAX_MOVES = 9; // TTT_BOARD_SIZE * TTT_BOARD_SIZE;

class TicTacToeBoard : public GameBoard {
   
public:
   enum Player {EMPTY = 0, X = 1, O = -1};
   
   TicTacToeBoard();
   
   virtual ~TicTacToeBoard() {
//      std::cout << "TicTacToeBoard Destructor" << std::endl;
   }
   
   //Fills in a vector with all possible moves on the current board state for
   // the current player
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;
   
   // Applies a valid move to the board, updating the board state accordingly
   virtual void ApplyMove(GameMove *move);
   
   // Undoes the last move applied to the board, restoring it to the state it was
   // in prior to the most recent move
   virtual void UndoLastMove();
   
   // Creates an OthelloMove object on the heap. Whoever calls this method is
   // responsible for managing the move's lifetime
   virtual GameMove *CreateMove() const {return new TicTacToeMove;}
   
   // returns char value of a winner after searching the board
   int CheckWinner() const;
   
   // Returns true if the game is finished.
   virtual bool IsFinished() const {
      return CheckWinner() != EMPTY || mMoveCount == MAX_MOVES;
   }
   
   // Returns a string representation for the given player value
   virtual std::string GetPlayerString(char player) {
         return (player == X ? "X" : "O");
   }
   
private:
   friend class TicTacToeView;
   
   // NOTE: we inherit mNextPlayer, mValue, and mHistory from GameBoard.
   char mBoard[TTT_BOARD_SIZE][TTT_BOARD_SIZE] = {};
   int mMoveCount = 0;  // keep track of moves applied
};

#endif
