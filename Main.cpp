#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int const row = 4;
int const column = 4;

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
void getMove(){
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
          (rowChoice > 0) && 
          (columnChoice < column) &&
          (columnChoice > 0))
          {
            cout << "\nThis entry is valid.\n";
                go = false;
          }
          if (go){
            cout << " \nYour entry does not match the format specified above, or you have gone outside the grid.\nPlease try again.\n";
          }
    }while(go);
  }
  void setBoard(char board[row][column]){
    for (int i = 0; i < row; ++i){
      for (int j = 0; j < column; ++j){
        board[i][j] = ' ';
      }
    }
  }


int main() {

  ifstream mineFile;
  //ifstream gameFile;
  char mines[row][column];
  char gameBoard[row][column];
  string foo;

  

  cout << "\nMINE BOARD\n";
  getBoard(mineFile, mines);
  //cout << "\nGAME BOARD\n";
  //getBoard(gameFile, gameBoard);
  setBoard(gameBoard);
  displayBoard(mines);
  displayBoard(gameBoard);
  getline(cin, foo);
  getMove();
  


  
  
  
}
