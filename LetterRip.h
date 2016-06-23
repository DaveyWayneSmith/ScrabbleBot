//
// Created by Edward on 6/21/2016.
//

#ifndef SCRABBLEBOT_LETTERRIP_H
#define SCRABBLEBOT_LETTERRIP_H

using namespace std;
#include <string>
#include "definitions.h"
#include "board.h"

class LetterRip {
    board* gameBoard;
    unsigned int metaBoard[BOARD_SIZE];
public:
    LetterRip(board* theBoard);
    placement getMove(string tray); // generate the ultimate move
};


#endif //SCRABBLEBOT_LETTERRIP_H
