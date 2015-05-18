// Matt Hopps
// Project3
// TicTacToeView.h
#ifndef __TICTACTOEVIEW_H
#define __TICTACTOEVIEW_H

#include "GameView.h"
#include "TicTacToeBoard.h"
#include <iostream>

class TicTacToeView : public GameView {
private:
   TicTacToeBoard *mTicTacToeBoard;
   virtual void PrintBoard(std::ostream &s) const;
   
public:
   TicTacToeView(GameBoard *b)
      : mTicTacToeBoard(dynamic_cast<TicTacToeBoard*>(b)) {}
};

#endif
