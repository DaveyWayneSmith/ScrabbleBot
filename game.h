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
    DictTrie dictionary = DictTrie();
    short currPlayer;
    short numPlayers;
    vector<player> players;
    pile tilePile;
    LetterRip theAI = LetterRip(&gameBoard, &dictionary);
    PlayerManager manager = PlayerManager(&theAI);
    vector<placement> extend(placement move); // computes a list of all words that extend off of a given placement
public:
    void start(); // start the game
    int play(placement move); // accept a placement from a player. returns the score if successful, -1 otherwise
    void display(); // display the current state of the game
    game(); // default constructor
    game(vector<bool> playerType); // constructor that specifies number of players
    void init(vector<bool> playerType); // delegate constructor
    bool validate(placement origMove, vector<placement> *exts); // validates a player move
};


#endif //SCRABBLEBOT_GAME_H
