//
// Created by Edward on 5/19/2016.
//

#ifndef SCRABBLEBOT_GAME_H
#define SCRABBLEBOT_GAME_H

#include <vector>
#include "board.h"
#include "pile.h"
#include "PlayerManager.h"


class game {
    board gameBoard = board();
    short currPlayer;
    short numPlayers;
    vector<player> players;
    pile tilePile;
    LetterRip theAI = LetterRip(&gameBoard);
    PlayerManager manager = PlayerManager(&theAI);
    // TODO This is public only for debugging
    //vector<placement> extend(placement move); // computes a list of all words that extend off of a given placement
    bool dictCheck(string word);
public:
    void start(); // start the game
    int play(placement move); // accept a placement from a player. returns the score if successful, -1 otherwise
    void display(); // display the current state of the game
    game(); // default constructor
    game(vector<bool> playerType); // constructor that specifies number of players
    void init(vector<bool> playerType); // delegate constructor
    vector<placement> extend(placement move); // computes a list of all words that extend off of a given placement
    bool validate(placement origMove, vector<placement> *exts); // validates a player move
};


#endif //SCRABBLEBOT_GAME_H
