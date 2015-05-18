// Matt Hopps
// Project3
// OthelloView.h
#ifndef __OTHELLOVIEW_H
#define __OTHELLOVIEW_H
#include "OthelloBoard.h"
#include "GameView.h"
#include <iostream>

class OthelloView : public GameView {
private:
	OthelloBoard *mOthelloBoard;
	virtual void PrintBoard(std::ostream &s) const;

public:
   OthelloView(GameBoard *b) : mOthelloBoard(dynamic_cast<OthelloBoard*>(b)) {}
};

#endif