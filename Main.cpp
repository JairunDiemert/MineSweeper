#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int const row = 4;
int const column = 4;

class Move 
{ 
    public: 
    char clickType;
    int rowChoice;
    int columnChoice;

    Move();
    Move(char click, int row, int column);
    void setClickType(char click);
    void setRowChoice(int row);
    void setColumnChoice(int column);
    char getClickType();
    int getRowChoice();
    int getColumnChoice();
    string getMoveString();
}; 

Move::Move(){
  setClickType('_');
  setRowChoice(-1);
  setColumnChoice(-1);
}   
Move::Move(char click, int row, int column){
  setClickType(click);
  setRowChoice(row);
  setColumnChoice(column);
}
void Move::setClickType(char click) 
{ 
    clickType = click;  
}
void Move::setRowChoice(int row) 
{ 
    rowChoice = row;  
}
void Move::setColumnChoice(int column) 
{ 
    columnChoice = column;  
} 
char Move::getClickType(){
  return clickType;
}
int Move::getRowChoice(){
  return rowChoice;
}
int Move::getColumnChoice(){
  return columnChoice;
}
string Move::getMoveString(){
  string moveValues = "";
  moveValues += getClickType();
  moveValues += " ";
  moveValues += getRowChoice() + '0';
  moveValues += " ";
  moveValues += getColumnChoice() + '0';
  return moveValues;
}

void openFile(ifstream& myFile){
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
}
void getBoard(ifstream& myFile, char mines[row][column] ){
  openFile(myFile);
  int k = 0;
  string line;
  while (getline(myFile, line)) {
    for (int i = 0; i < column; ++i){
       mines[k][i] = line[i];
    }
    ++k;
  }
}
void displayBoard(char board[row][column]){
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
}
Move getMove(){
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
    //cout << "\n\n" << clickType << " " << rowChoice << " " << columnChoice; keep her to display return value when needed.
    return move;
  }
  void setBoard(char board[row][column]){
    for (int i = 0; i < row; ++i){
      for (int j = 0; j < column; ++j){
        board[i][j] = ' ';
      }
    }
  }
  
  int mineCounter(char mines[row][column], Move move){
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
  }
  void setMove(char mines[row][column], char gameBoard[row][column], Move move, bool& gameOver){
    int numMines = mineCounter(mines, move);
    if (move.getClickType() == 'c' || move.getClickType() == 'C'){
      if (gameBoard[move.getRowChoice()][move.getColumnChoice()] == ' '){
        if (mines[move.getRowChoice()][move.getColumnChoice()] != '*'){
          gameBoard[move.getRowChoice()][move.getColumnChoice()] = numMines + '0';
        }
      }
      else if (gameBoard[move.getRowChoice()][move.getColumnChoice()] != ' '){
        cout << "\nDuplicate entry.\nPlease try again.\n";
      }
      else{
        cout << "\nYOU HIT A MINE\n  GAME OVER\n";
        gameOver = true;
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

  }

int main() {

  ifstream mineFile;
  char mines[row][column];
  char gameBoard[row][column];
  string foo;
  Move move;
  bool gameOver = false;


  cout << "\nMINE BOARD\n";
  getBoard(mineFile, mines);
  setBoard(gameBoard);
  displayBoard(mines); //here to display location of mines when needed
  displayBoard(gameBoard);
  getline(cin, foo);

  do{
  move = getMove();
  setMove(mines, gameBoard, move, gameOver);
  if (!gameOver){
    displayBoard(gameBoard);
  }
  }while(!gameOver);
  
}
