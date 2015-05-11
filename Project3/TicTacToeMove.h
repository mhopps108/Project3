//
//  TicTacToeMove.h
//  Project3
//

#ifndef __TICTACTOEMOVE_H
#define __TICTACTOEMOVE_H
#include "GameMove.h"
//#include "TicTacToeBoard.h"


class TicTacToeMove : public GameMove {
private:
   friend class TicTacToeBoard;
   
   int mRow, mCol;
   
   TicTacToeMove();
   
   TicTacToeMove(int row, int col);
   
public:
   // destructor
   virtual ~TicTacToeMove() {}
   
   virtual GameMove& operator=(const std::string &);
   
   virtual bool Equals(const GameMove &other) const;
   
   virtual operator std::string() const;
   
//   inline bool IsPass() const {return mRow == -1 && mCol == -1;}
   
};


#endif
