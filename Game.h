//File: Game.h
//Author: Jairun Diemert
//Class: COP3014
//Project: 2
//Description: This is the header file for the Game class.

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Move.h"

class Game 
{
  public:
  int static const row = 4;
  int static const column = 4;

  void openFile(ifstream& myFile);
  void getBoard(ifstream& myFile, char mines[row][column] );
  void displayBoard(char board[row][column]);
  Move getMove();
  void setBoard(char board[row][column]);
  int getTotalMineCount(char board[row][column]);
  int mineCounter(char mines[row][column], Move move);
  bool getGameStatus(char mines[row][column], char gameBoard[row][column]);
  void recursiveSearch(char mines[row][column], char gameBoard[row][column], Move move);
  void setMove(char mines[row][column], char gameBoard[row][column], Move move, bool& gameOver);
  void playGame();
};

#endif 