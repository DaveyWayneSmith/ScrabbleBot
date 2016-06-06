//
// Created by Edward on 5/19/2016.
//

#include <iostream>
#include <algorithm>
#include "board.h"

/*
 * Default constructor for board
 * Initializes boardArr[] to all blanks (' ');
 * Initializes the multMap[] which contains information about which spaces contain multipliers
 * Initializes valMap[] which contains the point values of each character
 */
board::board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        boardArr[i] = ' ';
    }
    multMap[3] = DL;
    multMap[11] = DL;
    multMap[36] = DL;
    multMap[38] = DL;
    multMap[45] = DL;
    multMap[52] = DL;
    multMap[59] = DL;
    multMap[92] = DL;
    multMap[96] = DL;
    multMap[98] = DL;
    multMap[102] = DL;
    multMap[108] = DL;
    multMap[116] = DL;
    multMap[122] = DL;
    multMap[126] = DL;
    multMap[128] = DL;
    multMap[132] = DL;
    multMap[165] = DL;
    multMap[172] = DL;
    multMap[179] = DL;
    multMap[186] = DL;
    multMap[188] = DL;
    multMap[213] = DL;
    multMap[221] = DL;
    multMap[16] = DW;
    multMap[28] = DW;
    multMap[32] = DW;
    multMap[42] = DW;
    multMap[48] = DW;
    multMap[56] = DW;
    multMap[64] = DW;
    multMap[70] = DW;
    multMap[154] = DW;
    multMap[160] = DW;
    multMap[168] = DW;
    multMap[176] = DW;
    multMap[182] = DW;
    multMap[192] = DW;
    multMap[196] = DW;
    multMap[208] = DW;
    multMap[20] = TL;
    multMap[24] = TL;
    multMap[76] = TL;
    multMap[80] = TL;
    multMap[84] = TL;
    multMap[88] = TL;
    multMap[136] = TL;
    multMap[140] = TL;
    multMap[144] = TL;
    multMap[148] = TL;
    multMap[200] = TL;
    multMap[204] = TL;
    multMap[0] = TW;
    multMap[7] = TW;
    multMap[14] = TW;
    multMap[105] = TW;
    multMap[119] = TW;
    multMap[210] = TW;
    multMap[217] = TW;
    multMap[224] = TW;

    valMap['A'] = 1;
    valMap['B'] = 3;
    valMap['C'] = 3;
    valMap['D'] = 2;
    valMap['E'] = 1;
    valMap['F'] = 4;
    valMap['G'] = 2;
    valMap['H'] = 4;
    valMap['I'] = 1;
    valMap['J'] = 8;
    valMap['K'] = 5;
    valMap['L'] = 1;
    valMap['M'] = 3;
    valMap['N'] = 1;
    valMap['O'] = 1;
    valMap['P'] = 3;
    valMap['Q'] = 10;
    valMap['R'] = 1;
    valMap['S'] = 1;
    valMap['T'] = 1;
    valMap['U'] = 1;
    valMap['V'] = 4;
    valMap['W'] = 4;
    valMap['X'] = 8;
    valMap['Y'] = 4;
    valMap['Z'] = 10;
    valMap['*'] = 0;
    valMap[' '] = -200; // for debugging purposes
    valMap['_'] = -200; // these values should never be added to a score

}

/*
 * Prints out a representation of the current state of the board to stdout
 */
void board::display() {
    cout << HEADER;
    for (int i = 0; i < BOARD_SIDE_LEN * 2 + 1; i++) {
        if (i % 2 == 0) {
            cout << BOARD_BAR;
        } else {
            cout << '|';
            for (int j = 0; j < 15; j++) {
                int currLoc = j + (i / 2) * BOARD_SIDE_LEN;
                char lett = boardArr[currLoc];
                if (lett == ' ' && multMap.find(currLoc) != multMap.end()) { // if the space is empty, need to check if it is a special tile
                    int mapVal = multMap.at(currLoc);
                    if (mapVal == DL) { // extra check because end iterator evaluates to 0 (for some reason)
                        cout << "\033[1;36md l\033[0m";
                    } else if (mapVal == TL) {
                        cout << "\033[1;34mt l\033[0m";
                    } else if (mapVal == DW) {
                        cout << "\033[1;35md w\033[0m";
                    } else if (mapVal == TW) {
                        cout << "\033[1;31mt w\033[0m";
                    }
                    cout << '|';
                } else if (lett == ' ' && currLoc == CENTER) {
                    cout << " * |";
                } else {
                    cout << ' ';
                    cout << boardArr[j + (i / 2) * BOARD_SIDE_LEN];
                    cout << " |";
                }
            }
        }
        cout << '\n';
    }
    cout << HEADER;
}

/*
 * @param move A placement struct to be placed on the board
 * @return 0 (should always return 0. Any other value indicates error)
 *
 * Places a move on the board.
 * NO ERROR CHECKING OF ANY KIND IS DONE IN THIS METHOD!
 * At this point, the placement is assumed to be a valid move.
 * If for some reason a part of the move overlaps with something on the board, the characters in the placemnt
 * will override those already on the board.
 * Intersections within the bounds of the new word should be represented as '_' in the placement
 *
 * This method also removes any multipliers that this move covers. For this reason, calcScore of the move
 * must be called before the move is placed on the board.
 * Also sets the empty parameter of the board to false.
 */
int board::place(placement move) {
    int loc = TRANSPOSE(move.loc, move.dir);
    string word = move.word;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] != '_') {
            boardArr[TRANSPOSE(loc + i, move.dir)] = word[i];
            multMap[TRANSPOSE(loc + i, move.dir)] = NO;
        }
    }
    empty = false;
    return 0;
}

/*
 * @param move A placement struct to calculate the score for
 * @return The score value of the placement
 *
 * Calculates the raw score of a single placement. Accounts for multipliers and wildcard tiles.
 */
int board::calcScore(placement move) {
    int norm_loc = TRANSPOSE(move.loc, move.dir);
    string word = move.word;
    short multiplier = 1;
    int score = 0;
    char currChar;
    for (int i = 0; i < word.length(); i++) {
        currChar = word[i];
        if (currChar == '_') {
            currChar = boardArr[TRANSPOSE(norm_loc + i, move.dir)];
        } else if (currChar == '*') {
            wild_loc.push_back(TRANSPOSE(norm_loc + i, move.dir));
        }
        if (currChar != '*' && count(wild_loc.begin(), wild_loc.end(), TRANSPOSE(norm_loc + i, move.dir)) != 0) {
            currChar = '*';
        }
        if (multMap.find(TRANSPOSE(norm_loc + i, move.dir)) != multMap.end()) {
            int mapVal = multMap.at(TRANSPOSE(norm_loc + i, move.dir));
            if (mapVal == DL) {
                score += 2 * valMap.at(currChar);
            } else if (mapVal == TL) {
                score += 3 * valMap.at(currChar);
            } else if (mapVal == DW) {
                multiplier *= 2;
                score += valMap.at(currChar);
            } else if (mapVal == TW){
                multiplier *= 3;
                score += valMap.at(currChar);
            } else { // mapVal == NO
                score += valMap.at(currChar);
            }
        } else {
            score += valMap.at(currChar);
        }
    }
    score *= multiplier;
    return score;
}

/*
 * @param moves A vector of placements
 * @return the sum of the score of all placements
 */
int board::calcScore(vector<placement> moves) {
    int score = 0;
    for (auto move : moves) {
        score += calcScore(move);
    }
    return score;
}

/*
 * @param loc An index at which to retrive a character off of the board
 * @param trans Whether or not the index should be transposed before indexing
 *
 * Getter method that accounts for transposed indices. This functionality is such that placing words vertically
 * and horizontally does not have to be treated as a separate cases. Instead, always wrap user specified locations in the
 * TRANSPOSE() macro, then pass that location into this method with the transpose flag set to whether or not the move
 * was horizontal or vertical, (also a user input) and it will work everything out.
 */
char board::get(int loc, int trans) {
    return boardArr[TRANSPOSE(loc, trans)];
}

/*
 * @return whether or not the board has anything on it
 *
 * This method is used for validation of the first move of the game
 */
bool board::isempty() {
    return empty;
}