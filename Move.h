//File: Move.h
//Author: Jairun Diemert
//Class: COP3530
//Project: 2
//Description: This is the header file for the Move class.

#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>
using namespace std;

class Move 
{ 
    private: 
    char clickType;
    int rowChoice;
    int columnChoice;

    public:
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

#endif 