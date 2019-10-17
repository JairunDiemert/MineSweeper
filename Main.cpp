#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int const row = 4;
int const column = 4;

void openFile(ifstream& myFile){
  string fileName;
  cout << "File Name: ";
  cin >> fileName;
  
  myFile.open(fileName.c_str());
  if (!myFile.is_open()){
    cout << "File open ERROR" << endl;
  }
  if (myFile.is_open()){
    cout << "File is OPEN" << endl;
  }
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



int main() {

  ifstream mineFile;
  ifstream gameFile;
  char mines[row][column];
  char gameBoard[row][column];

  char flag = 'F';
  char bomb = 'X';

  cout << "\nMINE BOARD\n";
  getBoard(mineFile, mines);
  cout << "\nGAME BOARD\n";
  getBoard(gameFile, gameBoard);
  displayBoard(mines);
  displayBoard(gameBoard);

  
  
  
}
