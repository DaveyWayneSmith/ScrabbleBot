//
// Created by Edward on 5/19/2016.
//

#ifndef SCRABBLEBOT_GAME_H
#define SCRABBLEBOT_GAME_H

#include "board.h"


class game {
    board gameBoard;
    short currPlayer;
public:
    void start(); // start the game
    bool play(); // wait for player to play
    void display(); // display the current state of the game
};


#endif //SCRABBLEBOT_GAME_H
