// Matt Hopps
//
// Project3
// main.cpp
#include "GameBoard.h"
#include "GameExceptions.h"
#include "GameView.h"
#include "GameMove.h"

#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"

#include "TicTacToeView.h"
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// prototypes
void GamePlay(GameBoard *, GameView *);   // new
void ProcessCommand(string, GameBoard *);
bool IsPossMove(const GameMove *, const GameBoard *);
void PrintPossMoves(const GameBoard *);
void CleanUpMoveVector(vector<GameMove *> &);

int main(int argc, char* argv[]) {
   // Initialization
   GameBoard *board;
   GameView *v;
   const int othelloGame = 1;
   const int ticTacToe = 2;
   const int endGame = 3;

   int gameChoice = 0;
   do {

      cout << "\nWhat game do you want to play? \n"
         "1) Othello \n2) Tic Tac Toe \n3) Exit \nSelection: ";
      cin >> gameChoice;

      if (gameChoice == othelloGame) {
         board = new OthelloBoard();
         v = new OthelloView(board);
      }
      else if (gameChoice == ticTacToe) {
         board = new TicTacToeBoard();
         v = new TicTacToeView(board);
      }
      else {
         exit(0);    // end game
      }
   
      GamePlay(board, v);
   
   } while (gameChoice != endGame);

}

//
void GamePlay(GameBoard *board, GameView *v) {
   string userInput; // a string to hold the user's command choice
   
   do {  // game loop for each players turn
      cout << *v << endl;  // print current board
      cout << board->GetPlayerString(board->GetNextPlayer()) << "'s";
      cout << " turn" << endl << "Possible moves: " << endl;
      PrintPossMoves(board);  // prints possible moves for current player
      
      do {
         cout << "Enter a command: ";
         getline(cin, userInput);
         ProcessCommand(userInput, board);
      } while (!(userInput.find("move") != string::npos ||
               userInput.find("undo") != string::npos || userInput == "quit"));

   } while (!board->IsFinished() && userInput != "quit");

   // print winner
   if (userInput != "quit") {
      cout << *v << endl;
      cout << (board->GetValue() > 0 ?
               board->GetPlayerString(1) : board->GetPlayerString(-1));
      cout << " Wins!" << endl;
   }
}


// process and run command from user input
void ProcessCommand(string input, GameBoard *board) {
   // read command from user inputted string
   istringstream iss(input);
   string command;  // the command entered
   iss >> command;
   
   if (command == "move") {
      string moveStr;  // the move entered
      iss >> moveStr;
      GameMove *m = board->CreateMove();
//      unique_ptr<GameMove> m = board->CreateMove();
      
      try {
         *m = moveStr;
         if (IsPossMove(m, board)) {
            board->ApplyMove(m);
         }
         else {
            cout << "Not a valid move.. " << (string)*m <<  endl;
            delete m;
         }
      }
      catch (OthelloException &oEx) {
         cout << "Caught exception, with message " << oEx.what() << endl;
         delete m;
      }
   }
   else if (command == "undo") {
      int num;  // number of moves to undo
      iss >> num;
      for (int i = 0; i < num; i++) {
         board->UndoLastMove();
      }
   }
   else if (command == "showValue") {
      cout << "\nBoard Value: " << board->GetValue() << endl << endl << endl;
   }
   else if (command == "showHistory") {
      const vector<GameMove *> *history = board->GetMoveHistory();
      int count = (int)history->size();
      
      for (auto itr = history->rbegin(); itr != history->rend(); ++itr) {
         cout << (count % 2 == 1 ?
                  board->GetPlayerString(1) : board->GetPlayerString(-1));
         cout << ": " << (string)(**itr) << endl;
         count--;
      }
      cout << endl;
   }
//   else if (command == "exit") {
//      exit(0); // end program
//   }
}

// check if user move is a possible move
bool IsPossMove(const GameMove *m, const GameBoard *board) {
   vector<GameMove *> pMoves; // a holder for possible moves
   board->GetPossibleMoves(&pMoves);
   
   bool found = false;
   for (GameMove *move : pMoves) {
      //   for (auto move : pMoves) {
      if (*m == *move) {
         found = true;  // found it
      }
   }
   CleanUpMoveVector(pMoves);
   return found;
}

// prints possible OthelloMoves
void PrintPossMoves(const GameBoard *board) {
   vector<GameMove *> possMoves; // a holder for possible moves
   if (board == nullptr)
      cout << "board is null" << endl;
   board->GetPossibleMoves(&possMoves);
   
   for (GameMove *move : possMoves) {  // print all possible moves
      cout << (string)*move << " ";
   }
   cout << endl;
   CleanUpMoveVector(possMoves);
}

// delete heap ptrs and clear OthelloMove vector
void CleanUpMoveVector(vector<GameMove *> &list) {
   for (GameMove *move : list) {
      delete move;
   }
   list.clear();
}


