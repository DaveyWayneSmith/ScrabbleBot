//
// Created by Edward on 5/19/2016.
//

#ifndef SCRABBLEBOT_BOARD_H
#define SCRABBLEBOT_BOARD_H

using namespace std;
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include "definitions.h"


class board {
    string BOARD_BAR = "-------------------------------------------------------------";
    string HEADER =    "                          SCRABBLE                           \n";
    char boardArr[BOARD_SIZE];
    map<int, int> multMap;
    map<char, int> valMap;
    vector<int> wild_loc;
    bool empty = true;
public:
    board(); // constructor
    void display(); //display the board
    int place(placement move); // place word on the board
    int calcScore(placement move); // calculates the score of a placement
    int calcScore(vector<placement> moves);
    char get(int loc); // get a character off of the board
    char get(int loc, int trans); // get a character off the board; the second input specifies whether or not to transpose the given location
    bool isempty(); // returns whether or not there is anything on the board
    char get_adj(int loc, int trans, char dir); // get adjacent characters off of the board. The second input can be 'n', 's', 'e', or 'w'
    string get_adj_string(int loc, int trans, char dir); // get the longest possible string off of the board in any given direction, not including the given location
    bool checkBounds(placement test); // check if a placement will fit on the board (the AI uses this)
};


#endif //SCRABBLEBOT_BOARD_H
