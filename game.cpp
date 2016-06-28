//
// Created by Edward on 5/19/2016.
//

#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include "game.h"

/*
 * Contains the game loop
 * Gets moves from user input
 * If the move is valid,
 *      it is placed on the board
 *      The score of the player is incremented
 *      The game advances to the next player's turn
 * Otherwise,
 *      the score and state of the board are unchanged
 *      the game advances to the next player
 */
void game::start() {
    int maxscore = 0;
    display();
    while (maxscore < SCORE_CAP) {
        for (auto p:players) {
            if (p.score > maxscore) {
                maxscore = p.score;
            }
        }
        int score = play(manager.getMove(players[currPlayer]));
        if (score != -1) {
            players[currPlayer].score += score;
        }
        currPlayer = ++currPlayer % numPlayers;
        display();
    }
}



/*
 * @param move The move to potentially be placed on the board
 * @return the score of the move if it was valid, -1 otherwise
 *
 * Validates moves and placed them on the board if they are valid.
 * Also replaces letters in the current player's tray if the move was valid
 * Returns the score of a valid move, -1 if not valid
 */
int game::play(placement move) {
    int score = 0;
    vector<placement> ext = extend(move);
    if (!validate(move, &ext)) return -1;
    score = gameBoard.calcScore(ext);
    gameBoard.place(move);

    // replace used characters
    string tray = players[currPlayer].tray;
    int idx;
    for (auto c : move.word) {
        if (c == '_') { // if this is an intersection, then continue
            continue;
        } else if (tray.find(c) == std::string::npos) { // we need to replace a wildcard
            idx = (int) tray.find('*');
        } else {
            idx = (int) tray.find(c);
        }
        players[currPlayer].tray[idx] = tilePile.draw();
    }
    return score;
}

/*
 * Prints a representation of the current state of the game to stdout
 */
void game::display() {
    gameBoard.display();
    for (int i = 0; i < numPlayers; i++) {
        fprintf(stdout, "Player %d Score: %d\n", i + 1, players[i].score, i + 1);
    }
    fprintf(stdout, "\nIt's currently Player %d's turn\n", currPlayer + 1);
}

/*
 * Default constructor
 * Creates a game class with 2 players
 */
game::game() {
    vector<bool> type = vector<bool>(2);
    type.push_back(0);
    type.push_back(0);
    init(type);
}

/*
 * @param num The number of players this game should handle
 *
 * Constructor that allows specification of number of players
 */
game::game(vector<bool> playerType) {
    init(playerType);
}

/*
 * @param num the number of players this game will handle
 *
 * Delegation constructor that instantiates necessary information for the game
 */
void game::init(vector<bool> playerType) {
    tilePile = pile();
    numPlayers = (short) playerType.size();
    players = vector<player>();
    string tray;
    for (int i = 0; i < numPlayers; i++) {
        tray = "";
        while (tray.length() < TRAY_SIZE) {
            tray.push_back(tilePile.draw());
        }
        players.push_back(player{0, tray, playerType[i]});
    }
    currPlayer = 0;
}

/*
 * @param move A placement struct that specifies a move to be played
 * @return A vector of placement structs specifying all char sequences that intersect with the given placement
 *
 * Calculates all char sequences that intersect with a given move. Will extend char sequences off of every
 * inputted character until a blank or the edge of the board is found.
 */
vector<placement> game::extend(placement move) {
    vector<placement> result;

    //input direction extension
    string horz_ext;
    horz_ext += move.word[0];
    int curr_Loc = TRANSPOSE(move.loc, move.dir) - 1;
    int return_loc = move.loc;
    // valid locations are within or equal to lo and hi
    int lo_obds = TRANSPOSE(move.loc, move.dir) / 15 * 15;
    int hi_obds = lo_obds + 14;
    while (curr_Loc >= lo_obds && gameBoard.get(curr_Loc, move.dir) != ' ') {
        horz_ext = gameBoard.get(curr_Loc, move.dir) + horz_ext;
        return_loc = TRANSPOSE(curr_Loc, move.dir);
        curr_Loc--;
    }
    curr_Loc = TRANSPOSE(move.loc, move.dir) + 1;
    int i = 1;
    while (curr_Loc <= hi_obds && gameBoard.get(curr_Loc, move.dir) != ' ' || i < move.word.length()) {
        if (gameBoard.get(curr_Loc, move.dir) == ' ' && move.word[i] != ' ') {
            horz_ext = horz_ext + move.word[i];
        } else {
            horz_ext = horz_ext + gameBoard.get(curr_Loc, move.dir);
        }
        i++;
        curr_Loc++;
    }
    if (horz_ext.length() > 1) {
        result.push_back(placement{return_loc, move.dir, horz_ext});
    }
    //For each letter, extend in cross direction
    for(i = 0; i < move.word.length(); i++) {
        if (move.word[i] != '_') {
            string vert_ext;
            vert_ext += move.word[i];
            curr_Loc = TRANSPOSE(move.loc, move.dir) + i - 15;
            return_loc = TRANSPOSE(move.loc, move.dir);
            lo_obds = curr_Loc % 15;
            hi_obds = lo_obds + 210; // index of start of last row
            while (curr_Loc >= lo_obds && gameBoard.get(curr_Loc, move.dir) != ' ') {
                vert_ext = gameBoard.get(curr_Loc, move.dir) + vert_ext;
                return_loc = TRANSPOSE(curr_Loc, move.dir);
                curr_Loc -= 15;
            }

            curr_Loc = TRANSPOSE(move.loc, move.dir) + i + 15;
            while (curr_Loc <= hi_obds && gameBoard.get(curr_Loc, move.dir) != ' ') {
                vert_ext = vert_ext + gameBoard.get(curr_Loc, move.dir);
                curr_Loc += 15;
            }
            if (vert_ext.length() > 1) {
                result.push_back(placement{return_loc, !move.dir, vert_ext});
            }
        }
    }
    return result;
}

/*
 * @param origMove The placement struct of the new characters the player is playing
 * @param exts A pointer to the vector of placements that extend off of the players move,
 *      as calculated by the extend() method
 * @return whether or not the move is valid
 *
 * This method "polices" the game. It checks if the move violates any rules of the game and if so, returns false.
 * If the move is valid, it returns true. It also modifies exts to contain '*' anywhere a wildcard is necessary
 * in any of the extensions. This allows calcScore to properly calculate the score of the move without counting
 * wildcard tiles.
 */
bool game::validate(placement origMove, vector<placement> *exts) {
    // check if letters are in tray
    // this tray is only for debugging
    //string tray = "ABACTERIAL";
    string tray = players[currPlayer].tray.c_str();
    vector<int> stars;
    int wild_check = (int) count(tray.begin(), tray.end(), '*');
    for (int i = 0; i < origMove.word.length(); i++) {
        char c = origMove.word[i];
        if (c != '_') {
            bool found = tray.find(c) != std::string::npos;
            if (!found && wild_check > 0) {
                wild_check--;
                int star_loc = TRANSPOSE(TRANSPOSE(origMove.loc, origMove.dir) + i, origMove.dir);
                stars.push_back(star_loc);
            } else if (!found) {
                return false;
            }
        }
    }
    // check if word is touching another word
    if (gameBoard.isempty()) {
        // check that word crosses middle
        if (!(TRANSPOSE(origMove.loc, origMove.dir) <= 112
            && TRANSPOSE(origMove.loc, origMove.dir) + origMove.word.length() >= 112)) {
            return false;
        }
    } else {
        // check that word is adjacent to something
        if (exts->size() == 1 && exts->at(0).word.compare(origMove.word) == 0 ) {
            return false;
        }
    }
    // check that word will physically fit on board
    // basic checks
    if (origMove.loc < 0 || origMove.loc >= 225 || origMove.word.length() > 15) {
        return false;
    }
    // make sure it doesn't go off the edge
    int norm_loc = TRANSPOSE(origMove.loc, origMove.dir);
    int lo_obds = norm_loc / 15 * 15;
    int hi_obds = lo_obds + 14;
    if (norm_loc + origMove.word.length() - 1 > hi_obds) {
        return false;
    }
    // make sure it doesn't overlap with anything
    for (int i = 0; i < origMove.word.length(); i++) {
        if (gameBoard.get(norm_loc + i, origMove.dir) != ' ' && origMove.word[i] != '_') {
            return false;
        }
    }
    // look up every extension in the dictionary
    for (auto move : *exts) {
        if (!dictionary.containsWord(move.word)) {
            return false;
        }
//        if (!dictCheck(move.word)) {
//            return false;
//        }
    }

    // Replacing wildcards in extended words for calcScore
    if (stars.size() > 0) {
        for (int j = 0; j < exts->size(); j++) {
            placement *move = &exts->at(j);
            string *word = &move->word;
            int loc = TRANSPOSE(move->loc, move->dir);
            for (int k = 0; k < word->length(); k++) {
                int currloc = loc + k;
                for (auto star_loc : stars) {
                    if (TRANSPOSE(currloc, move->dir) == star_loc) {
                        exts->at(j).word.at(k) = '*';
                    }
                }

            }
        }
    }


    return true;
}
