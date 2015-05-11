//
//  TicTacToeBoard.h
//  Project3
//
#ifndef __Project3__TicTacToeBoard__
#define __Project3__TicTacToeBoard__

#include "GameBoard.h"
#include "GameMove.h"
#include "TicTacToeMove.h"
#include <vector>

const int TTT_BOARD_SIZE = 3;

class TicTacToeBoard : public GameBoard {
   
public:
   enum Player {EMPTY = 0, X = 1, O = -1};
   
   TicTacToeBoard();
   
   virtual ~TicTacToeBoard() {}
   
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;
   
   virtual void ApplyMove(GameMove *move);
   
   virtual void UndoLastMove();
   
   virtual GameMove *CreateMove() const {return new TicTacToeMove;}
   
   // returns char value of a winner after searching the board
   char CheckWinner() const;
   
   // Returns true if the game is finished.
   virtual bool IsFinished() const {
      return CheckWinner() == 1 || CheckWinner() == -1;
   }
   
   virtual std::string GetPlayerString(char player) {
         return (player == 1 ? "X" : "O");
   }
   
private:
   friend class TicTacToeView;
   
   // NOTE: we inherit mNextPlayer, mValue, and mHistory from GameBoard.
   char mBoard[TTT_BOARD_SIZE][TTT_BOARD_SIZE] = {};
};

#endif
