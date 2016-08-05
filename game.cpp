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
    int consecutivePassCount = 0;
    while (maxscore < SCORE_CAP) {
        for (auto p : players) {
            if (p.score > maxscore) {
                maxscore = p.score;
            }
        }
        placement p = manager.getMove(players[currPlayer]);
        int score = play(p);
        if (score >= 0) { // this is a normal move
            players[currPlayer].score += score;
            consecutivePassCount = 0;
            manager.placeMove(players[currPlayer], p);
        } else { // this is a special move
            if (score == PASS) {
                consecutivePassCount++;
            } else if (score == SWAP) {
                consecutivePassCount = 0;
            } else if (score == INVALID) {
                cout << "That move was invalid! You're turn has been skipped!\n";
                consecutivePassCount = 0;
            }
        }
        currPlayer = ++currPlayer % numPlayers;
        display();
        if (consecutivePassCount == 2) {
            cout << "Both players skipped in a row. Ending game...\n";
            break;
        }
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
    int result = 0;
    if (move.loc == PASS) {
        return PASS;
    } else if (move.loc == INVALID) {
        return INVALID;
    } else if (move.loc == SWAP) {
        result = SWAP;
        string tray = players[currPlayer].tray;
        int idx;
        string newchars;
        vector<int> locs;
        for (auto c : move.word) {
            idx = tray.find(c);
            if (idx == std::string::npos) {
                cout << "The letter " << c << " was not found in your tray.\n";
                return INVALID;
            } else {
                newchars.push_back(tilePile.draw()); // draw the new tile
                locs.push_back(idx); // keep track of where it needs to go
            }
        }
        for (auto loc : locs) {
            tilePile.replace(tray[loc]); // replace the old tile
            tray[loc] = newchars[0]; // put the new tile in the tray
            newchars.erase(0); // remove the new tile from the list of new tiles
        }
    } else {
        vector<placement> ext = extend(move);
        if (!validate(move, &ext)) {
            return INVALID;
        }
        result = gameBoard.calcScore(ext, true);
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
    }
    return result;
}

/*
 * Prints a representation of the current state of the game to stdout
 */
void game::display() {
    gameBoard.display();
    for (int i = 0; i < numPlayers; i++) {
        fprintf(stdout, "Player %d Score: %d\n", i + 1, players[i].score);
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
    // extend input word
    placement ext_move;
    string ext_lhs;
    string ext_rhs;
    ext_move.dir = move.dir;
    ext_lhs = gameBoard.get_adj_string(TRANSPOSE(move.loc, move.dir), move.dir, 'w');
    ext_rhs = gameBoard.get_adj_string((int) (TRANSPOSE(move.loc, move.dir) + move.word.size() - 1), move.dir, 'e');
    ext_move.loc = (int) TRANSPOSE(TRANSPOSE(move.loc, move.dir) - ext_lhs.size(), move.dir);
    string word = move.word;
    for (int i = 0; i < (int) (word.length()); i++) {
        if (word[i] == '_') {
            word[i] = gameBoard.get(TRANSPOSE(move.loc, move.dir) + i, move.dir);
        }
    }
    ext_move.word = ext_lhs + word + ext_rhs;
    result.push_back(ext_move);
    // compute cross checks
    for (int i = 0; i < (int) (word.length()); i++) {
        ext_move.dir = !move.dir;
        ext_lhs = gameBoard.get_adj_string(TRANSPOSE(move.loc, move.dir) + i, move.dir, 'n');
        ext_rhs = gameBoard.get_adj_string(TRANSPOSE(move.loc, move.dir) + i, move.dir, 's');
        ext_move.loc = (int) (TRANSPOSE(TRANSPOSE(TRANSPOSE(move.loc, move.dir) + i, ext_move.dir) - ext_lhs.size(), ext_move.dir));
        ext_move.word = ext_lhs + word[i] + ext_rhs;
        if ((ext_lhs.size() > 0 || ext_rhs.size() > 0) && move.word[i] != '_') {
            result.push_back(ext_move);
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
