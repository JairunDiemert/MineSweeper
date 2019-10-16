#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  ifstream myFile;
  myFile.open("fourXfour.in");
  string line;
  char tempChar;
  string lineArr[4];
  int row = 4;
  int column = 4;
  int k = 0;


  char mines[row][column];
  int counter = 0;
  if (!myFile.is_open()){
    cout << "File open ERROR" << endl;
  }
  while (getline(myFile, line)) {

    for (int i = 0; i < column; ++i){
      mines[k][i] = line[i];
      cout << "[" << k << "]" << "[" << i << "] : " << mines[k][i] << endl;
    }
    
    ++k;

  }
  cout << "\n";
  cout << "   0  1  2  3" << endl;
  cout << " +--+--+--+--+" << endl;
  for (int i = 0; i < row; ++i){
    cout << i;
    for (int j = 0; j < column; ++j){
      cout << "|" << mines[i][j] << " ";
    }
    cout << "|";
    cout << endl;
    cout << " +--+--+--+--+" << endl;
  }
}

