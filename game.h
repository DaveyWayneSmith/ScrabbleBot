//
// Created by Edward on 5/19/2016.
//

#ifndef SCRABBLEBOT_GAME_H
#define SCRABBLEBOT_GAME_H

#include <vector>
#include "board.h"
#include "pile.h"

typedef struct player {
    int score;
    string tray;
} player;


class game {
    board gameBoard;
    short currPlayer;
    short numPlayers;
    vector<player> players;
    pile tilePile;
    bool validate(placement move, int* cross_loc); // checks if a placement is valid
public:
    void start(); // start the game
    int play(placement move); // accept a placement from a player. returns the score if successful, -1 otherwise
    void display(); // display the current state of the game
    game(); // default constructor
    game(short num); // constructor that specifies number of players
    void init(short num); // delegate constructor
};


#endif //SCRABBLEBOT_GAME_H
