//
// Created by Edward on 5/19/2016.
//

#include <iostream>
#include "board.h"

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
 * NO ERROR CHECKING OF ANY KIND IS DONE IN THIS METHOD
 * Places letters on board based on loc, dir and word contained in move
 * Removes any multipliers that the placed letters are on
 * Blank spaces are represented as '_' within the word string
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

int board::calcScore(vector<placement> moves) {
    int score = 0;
    for (auto move : moves) {
        score += calcScore(move);
    }
    return score;
}

char board::get(int loc) {
    return boardArr[loc];
}

/*
 * loc is the location to index. If trans is 1, this index is transposed before indexing the board.
 * If it is 0, the board is indexed with loc directly.
 */
char board::get(int loc, int trans) {
    return boardArr[TRANSPOSE(loc, trans)];
}

bool board::isempty() {
    return empty;
}

char board::get_adj(int loc, int trans, char dir) {
    if (trans) {
        map<char, char> transMap;
        transMap['n'] = 'w';
        transMap['w'] = 'n';
        transMap['e'] = 's';
        transMap['s'] = 'e';
        dir = transMap.at(dir);
        return get_adj(TRANSPOSE(loc, 1), 0, dir);
    }
    char result = ' ';
    if (loc > 14 && dir == 'n') {
        result = boardArr[loc - 15];
    } else if (loc % 15 > 0 && dir == 'w') {
        result = boardArr[loc - 1];
    } else if (loc % 15 < 14 && dir == 'e') {
        result = boardArr[loc + 1];
    } else if (loc < 210 && dir == 's') {
        result = boardArr[loc + 15];
    }
    return result;
}