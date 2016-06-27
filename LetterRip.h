//
// Created by Edward on 6/21/2016.
//

#ifndef SCRABBLEBOT_LETTERRIP_H
#define SCRABBLEBOT_LETTERRIP_H

using namespace std;
#include <string>
#include "definitions.h"
#include "board.h"
#include "myDictionary.h"

class LetterRip {
    board* gameBoard;
    myDictionary dict; //TODO maybe make this a pointer later
    unsigned int metaBoard[BOARD_SIZE];
public:
    LetterRip(board* theBoard);
    placement getMove(string tray); // generate the ultimate move
    vector<int> getAnchorPoints();  // gets a vector containing all anchor points
    unsigned int crossCheck(int i); // calculate a bit vector of possible characters at a given index
    void extendLeft(int idx, string word, string placement_word, string tray, placement* maxMove, int* maxScore);
    void extendRight(int idx, int start_idx, string copy, string placement_word, string tray, placement* maxMove, int* maxScore);
};


#endif //SCRABBLEBOT_LETTERRIP_H
