//File: Move.cpp
//Author: Jairun Diemert
//Class: COP3530
//Project: 2
//Description: This is the member function file for Move. 

#include <iostream>
#include "Move.h"

Move::Move(){
  setClickType('_');
  setRowChoice(-1);
  setColumnChoice(-1);
};   
Move::Move(char click, int row, int column){
  setClickType(click);
  setRowChoice(row);
  setColumnChoice(column);
};
void Move::setClickType(char click) 
{ 
    clickType = click;  
};
void Move::setRowChoice(int row) 
{ 
    rowChoice = row;  
};
void Move::setColumnChoice(int column) 
{ 
    columnChoice = column;  
}; 
char Move::getClickType(){
  return clickType;
};
int Move::getRowChoice(){
  return rowChoice;
};
int Move::getColumnChoice(){
  return columnChoice;
};
string Move::getMoveString(){
  string moveValues = "";
  moveValues += getClickType();
  moveValues += " ";
  moveValues += getRowChoice() + '0';
  moveValues += " ";
  moveValues += getColumnChoice() + '0';
  return moveValues;
};