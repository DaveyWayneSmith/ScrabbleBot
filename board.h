//
// Created by Edward on 5/19/2016.
//

#ifndef SCRABBLEBOT_BOARD_H
#define SCRABBLEBOT_BOARD_H

using namespace std;
#include <stdio.h>
#include <string>
#include <map>
#include "definitions.h"


class board {
    string BOARD_BAR = "-------------------------------------------------------------";
    string HEADER =    "                          SCRABBLE                           \n";
    char boardArr[BOARD_SIZE];
    map<int, int> multMap;
    map<char, int> valMap;
    bool validatePlace(short loc, short dir, string word);
public:
    board(); // constructor
    void display(); //display the board
    int place(short loc, short dir, string word); // place word on the board
    int calcScore(short loc, short dir, string word); // calculates the score of a move
};


#endif //SCRABBLEBOT_BOARD_H
