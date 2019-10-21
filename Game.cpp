//File: Game.cpp
//Author: Jairun Diemert
//Class: COP3530
//Project: 2
//Description: This is the member function file for Game. 

#include <iostream>
#include "Game.h"
#include "Move.h"

void Game::openFile(ifstream& myFile){
  bool go = true;
  string fileName;
  do{
    cout << "File Name: ";
    cin >> fileName;
    
    myFile.open(fileName.c_str());
    if (!myFile.is_open()){
      cout << "File open ERROR\n" << endl;
    }
    if (myFile.is_open()){
      cout << "File is OPEN" << endl;
      go = false;
    }
  }while(go);
};
void Game::getBoard(ifstream& myFile, char mines[row][column] ){
  openFile(myFile);
  int k = 0;
  string line;
  while (getline(myFile, line)) {
    for (int i = 0; i < column; ++i){
       mines[k][i] = line[i];
    }
    ++k;
  }
};
void Game::displayBoard(char board[row][column]){
  cout << "\n";
  cout << "   0  1  2  3" << endl;
  cout << " +--+--+--+--+" << endl;
  for (int i = 0; i < row; ++i){
    cout << i;
    for (int j = 0; j < column; ++j){
        cout << "|" << board[i][j] << " ";
    }
  cout << "|";
  cout << endl;
  cout << " +--+--+--+--+" << endl;
  }
};
Move Game::getMove(){
    char clickType;
    int rowChoice;
    int columnChoice;
    string choices;
    bool go = true;

    do{
      cout << "\nChoose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3:";
      getline(cin, choices);
      cout << "\nYou entered: " << choices;
      clickType = choices[0];
      rowChoice = choices[2] - '0';
      columnChoice = choices[4] - '0';
      if (((clickType == 'c') ||
          (clickType == 'C') ||
          (clickType == 'f') ||
          (clickType == 'F')) &&
          (isdigit(choices[2]) != 0) &&
          (isdigit(choices[4]) != 0) &&
          (rowChoice < row) &&
          (rowChoice >= 0) && 
          (columnChoice < column) &&
          (columnChoice >= 0))
          {
                go = false;
          }
          if (go){
            cout << " \nYour entry does not match the format specified above, or you have gone outside the grid.\nPlease try again.\n";
          }
    }while(go);
    Move move(clickType, rowChoice, columnChoice);
    return move;
  };
  void Game::setBoard(char board[row][column]){
    for (int i = 0; i < row; ++i){
      for (int j = 0; j < column; ++j){
        board[i][j] = ' ';
      }
    }
  };
  int Game::getTotalMineCount(char board[row][column]){
    int totalMines = 0;
    for (int i = 0; i < row; ++i){
      for (int j = 0; j < column; ++j){
        if (board[i][j] == '*'){
          ++totalMines;
        }
      }
    }
    return totalMines;
  };
  int Game::mineCounter(char mines[row][column], Move move){
    int numMines = 0;
    if ((move.getRowChoice() + 1 < row) &&
        (move.getRowChoice() + 1 >= 0) &&
        (mines[move.getRowChoice() + 1][move.getColumnChoice()] == '*')){
        ++numMines;
    }
    if ((move.getColumnChoice() + 1 < row) &&
        (move.getColumnChoice() + 1 >= 0) &&
        (mines[move.getRowChoice()][move.getColumnChoice() + 1] == '*')){
        ++numMines;
    }
    if ((move.getRowChoice() - 1 < row) &&
        (move.getRowChoice() - 1 >= 0) &&
        (mines[move.getRowChoice() - 1][move.getColumnChoice()] == '*')){
        ++numMines;
    }
    if ((move.getColumnChoice() - 1 < row) &&
        (move.getColumnChoice() - 1 >= 0) &&
        (mines[move.getRowChoice()][move.getColumnChoice() - 1] == '*')){
        ++numMines;
    }
    if ((move.getRowChoice() + 1 < row) &&
        (move.getRowChoice() + 1 >= 0) &&
        (move.getColumnChoice() + 1 < row) &&
        (move.getColumnChoice() + 1 >= 0) &&
        (mines[move.getRowChoice() + 1][move.getColumnChoice() + 1] == '*')){
        ++numMines;
    }
    if ((move.getRowChoice() + 1 < row) &&
        (move.getRowChoice() + 1 >= 0) &&
        (move.getColumnChoice() - 1 < row) &&
        (move.getColumnChoice() - 1 >= 0) &&
        (mines[move.getRowChoice() + 1][move.getColumnChoice() - 1] == '*')){
        ++numMines;
    }
    if ((move.getRowChoice() - 1 < row) &&
        (move.getRowChoice() - 1 >= 0) &&
        (move.getColumnChoice() + 1 < row) &&
        (move.getColumnChoice() + 1 >= 0) &&
        (mines[move.getRowChoice() - 1][move.getColumnChoice() + 1] == '*')){
        ++numMines;
    }
    if ((move.getRowChoice() - 1 < row) &&
        (move.getRowChoice() - 1 >= 0) &&
        (move.getColumnChoice() - 1 < row) &&
        (move.getColumnChoice() - 1 >= 0) &&
        (mines[move.getRowChoice() - 1][move.getColumnChoice() - 1] == '*')){
        ++numMines;
    }
    return numMines;
  };
  bool Game::getGameStatus(char mines[row][column], char gameBoard[row][column]){
    bool youWin = false;
    int cellsLeft = 0;
    int totalMines = getTotalMineCount(mines);
    for (int i = 0; i < row; ++i){
      for (int j = 0; j < column; ++j){
        if ((gameBoard[i][j] == ' ') || (gameBoard[i][j] == 'F')){
          ++cellsLeft;
        }
      }
    }
    if (cellsLeft == totalMines) {
      cout << "\n\nYOU WIN\n\n";
      youWin = true;
    }
    return youWin;
  };
  void Game::recursiveSearch(char mines[row][column], char gameBoard[row][column], Move move){

    if (gameBoard[move.getRowChoice()][move.getColumnChoice()] == '0'){
      if ((move.getRowChoice() + 1 < row) &&
          (move.getRowChoice() + 1 >= 0) &&
          (gameBoard[move.getRowChoice() + 1][move.getColumnChoice()] == ' ')){
            if (mines[move.getRowChoice() + 1][move.getColumnChoice()] != '*'){
              Move moveIterate('C', move.getRowChoice() + 1, move.getColumnChoice());
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice() + 1][move.getColumnChoice()] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getColumnChoice() + 1 < row) &&
          (move.getColumnChoice() + 1 >= 0) &&
          (gameBoard[move.getRowChoice()][move.getColumnChoice() + 1] == ' ')){
            if (mines[move.getRowChoice()][move.getColumnChoice() + 1] != '*'){
              Move moveIterate('C', move.getRowChoice(), move.getColumnChoice() + 1);
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice()][move.getColumnChoice() + 1] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getRowChoice() - 1 < row) &&
          (move.getRowChoice() - 1 >= 0) &&
          (gameBoard[move.getRowChoice() - 1][move.getColumnChoice()] == ' ')){
            if (mines[move.getRowChoice() - 1][move.getColumnChoice()] != '*'){
              Move moveIterate('C', move.getRowChoice() - 1, move.getColumnChoice());
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice() - 1][move.getColumnChoice()] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getColumnChoice() - 1 < row) &&
          (move.getColumnChoice() - 1 >= 0) &&
          (gameBoard[move.getRowChoice()][move.getColumnChoice() - 1] == ' ')){
            if (mines[move.getRowChoice()][move.getColumnChoice() - 1] != '*'){
              Move moveIterate('C', move.getRowChoice(), move.getColumnChoice() - 1);
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice()][move.getColumnChoice() - 1] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getRowChoice() + 1 < row) &&
          (move.getRowChoice() + 1 >= 0) &&
          (move.getColumnChoice() + 1 < row) &&
          (move.getColumnChoice() + 1 >= 0) &&
          (gameBoard[move.getRowChoice() + 1][move.getColumnChoice() + 1] == ' ')){
            if (mines[move.getRowChoice() + 1][move.getColumnChoice() + 1] != '*'){
              Move moveIterate('C', move.getRowChoice() + 1, move.getColumnChoice() + 1);
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice() + 1][move.getColumnChoice() + 1] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getRowChoice() + 1 < row) &&
          (move.getRowChoice() + 1 >= 0) &&
          (move.getColumnChoice() - 1 < row) &&
          (move.getColumnChoice() - 1 >= 0) &&
          (gameBoard[move.getRowChoice() + 1][move.getColumnChoice() - 1] == ' ')){
            if (mines[move.getRowChoice() + 1][move.getColumnChoice() - 1] != '*'){
              Move moveIterate('C', move.getRowChoice() + 1, move.getColumnChoice() - 1);
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice() + 1][move.getColumnChoice() - 1] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getRowChoice() - 1 < row) &&
          (move.getRowChoice() - 1 >= 0) &&
          (move.getColumnChoice() + 1 < row) &&
          (move.getColumnChoice() + 1 >= 0) &&
          (gameBoard[move.getRowChoice() - 1][move.getColumnChoice() + 1] == ' ')){
            if (mines[move.getRowChoice() - 1][move.getColumnChoice() + 1] != '*'){
              Move moveIterate('C', move.getRowChoice() - 1, move.getColumnChoice() + 1);
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice() - 1][move.getColumnChoice() + 1] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      if ((move.getRowChoice() - 1 < row) &&
          (move.getRowChoice() - 1 >= 0) &&
          (move.getColumnChoice() - 1 < row) &&
          (move.getColumnChoice() - 1 >= 0) &&
          (gameBoard[move.getRowChoice() - 1][move.getColumnChoice() - 1] == ' ')){
            if (mines[move.getRowChoice() - 1][move.getColumnChoice() - 1] != '*'){
              Move moveIterate('C', move.getRowChoice() - 1, move.getColumnChoice() + 1);
              int numMines = mineCounter(mines, moveIterate);
              gameBoard[move.getRowChoice() - 1][move.getColumnChoice() - 1] = numMines + '0';
              recursiveSearch(mines, gameBoard, moveIterate);
            }
          }
      }
  };
  void Game::setMove(char mines[row][column], char gameBoard[row][column], Move move, bool& gameOver){
    int numMines = mineCounter(mines, move);
    if (move.getClickType() == 'c' || move.getClickType() == 'C'){
      if (gameBoard[move.getRowChoice()][move.getColumnChoice()] == ' '){
        if (mines[move.getRowChoice()][move.getColumnChoice()] != '*'){
          gameBoard[move.getRowChoice()][move.getColumnChoice()] = numMines + '0';
          recursiveSearch(mines, gameBoard, move);
        }
        else {
        cout << "\nYOU HIT A MINE\n  GAME OVER\n";
        gameOver = true;
        }
      }
      else {
        cout << "\nDuplicate entry.\nPlease try again.\n";
      }
      
    }
    if (move.getClickType() == 'f' || move.getClickType() == 'F'){
      if (gameBoard[move.getRowChoice()][move.getColumnChoice()] == ' '){
        gameBoard[move.getRowChoice()][move.getColumnChoice()] = 'F';
      }
      else{
      gameBoard[move.getRowChoice()][move.getColumnChoice()] = ' ';
      }
    }
    if (!gameOver){
      gameOver = getGameStatus(mines, gameBoard);
    }
  };
  void Game::playGame() {
    ifstream mineFile;
    char mines[row][column];
    char gameBoard[row][column];
    string foo;
    Move move;
    bool gameOver = false;

    cout << "\nMINE BOARD\n";
    getBoard(mineFile, mines);
    setBoard(gameBoard);
    displayBoard(gameBoard);
    getline(cin, foo);

    do{
      move = getMove();
      setMove(mines, gameBoard, move, gameOver);

      if (!gameOver){
        displayBoard(gameBoard);
      }
    }while(!gameOver);
  };
  