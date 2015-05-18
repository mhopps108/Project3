// Matt Hopps
// Project3
// TicTacToeMove.h
#ifndef __TICTACTOEMOVE_H
#define __TICTACTOEMOVE_H
#include "GameMove.h"
#include <iostream>

class TicTacToeMove : public GameMove {
private:
   friend class TicTacToeBoard;
   
   int mRow, mCol;
   
   TicTacToeMove();
   
   TicTacToeMove(int row, int col);
   
public:
   static int mOnHeap;
   
   // destructor
   virtual ~TicTacToeMove() {}
   
   virtual GameMove& operator=(const std::string &);
   
   virtual bool Equals(const GameMove &other) const;
   
   virtual operator std::string() const;
   
//   static void* operator new(std::size_t sz){
//      mOnHeap++;
//      std::cout << "operator new: " << mOnHeap << " TTTMoves on the heap"
//         << std::endl;
//      return ::operator new(sz);
//   }
//   
//   static void operator delete(void* ptr, std::size_t sz) {
//      mOnHeap--;
//      std::cout << "operator delete: " << mOnHeap << " TTTMoves on the heap"
//         << std::endl;
//      ::operator delete(ptr);
//   }
};

#endif
