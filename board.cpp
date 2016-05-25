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

}

void board::display() {
    cout << HEADER;
    for (int i = 0; i < BOARD_SIDE_LEN * 2 + 1; i++) {
        if (i % 2 == 0) {
            cout << BOARD_BAR;
        } else {
            cout << '|';
            for (int j = 0; j < 15; j++) {
                cout << ' ';
                cout << boardArr[j + (i / 2) * BOARD_SIDE_LEN];
                cout << " |";
            }
        }
        cout << '\n';
    }
    cout << HEADER;
}

/*
 * NO OUT-OF-BOUNDS ERROR CHECKING
 */
int board::place(placement move) {
    short dir = move.dir;
    short loc = move.loc;
    string word = move.word;
    if (dir == HORZ) { // if horizontal
        for (int i = 0; i < word.length(); i++) {
            boardArr[loc + i] = word[i];
        }
    } else { // vertical placement
        for (int i = 0; i < word.length(); i++) {
            boardArr[loc + i * BOARD_SIDE_LEN] = word[i];
        }
    }
    return calcScore(move); //
}

int board::calcScore(placement move) {
    short loc = move.loc;
    short dir = move.dir;
    string word = move.word;

    short multiplier = 1;
    int score = 0;
    char currChar;
    int currLoc;
    for (int j = 0; j < word.length(); j++) {
        if (dir == HORZ) {
            currLoc = loc + j;
        } else {
            currLoc = loc + j * BOARD_SIDE_LEN;
        }
        currChar = word[j];
        if (currChar == '_') {
            score += valMap[boardArr[currLoc]];
        } else if (multMap.find(currLoc) != multMap.end() && multMap[currLoc] == DL) { // extra check because end iterator evaluates to 0 (for some reason)
            score += 2 * valMap[currChar];
        } else if (multMap[currLoc] == TL) {
            score += 3 * valMap[currChar];
        } else if (multMap[currLoc] == DW) {
            multiplier *= 2;
            score += valMap[currChar];
        } else if (multMap[currLoc] == TW) {
            multiplier *= 3;
            score += valMap[currChar];
        } else {
            score += valMap[currChar];
        }
    }
    score *= multiplier;
    return score;
}