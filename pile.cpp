//
// Created by Davey Smith on 5/17/16.
//

#include <vector>
#include <time.h>
#include <cstdlib>
#include "pile.h"

/*
 * Default constructor for the pile. Initializes frequencies of all the characters.
 */
pile::pile() {
    pileMap['A'] = 9;
    pileMap['B'] = 2;
    pileMap['C'] = 2;
    pileMap['D'] = 4;
    pileMap['E'] = 12;
    pileMap['F'] = 2;
    pileMap['G'] = 3;
    pileMap['H'] = 2;
    pileMap['I'] = 9;
    pileMap['J'] = 1;
    pileMap['K'] = 1;
    pileMap['L'] = 4;
    pileMap['M'] = 2;
    pileMap['N'] = 6;
    pileMap['O'] = 8;
    pileMap['P'] = 2;
    pileMap['Q'] = 1;
    pileMap['R'] = 6;
    pileMap['S'] = 4;
    pileMap['T'] = 6;
    pileMap['U'] = 4;
    pileMap['V'] = 2;
    pileMap['W'] = 2;
    pileMap['X'] = 1;
    pileMap['Y'] = 2;
    pileMap['Z'] = 1;
    pileMap['*'] = 2;

    srand(time(NULL));
}

/*
 * @return a character "drawn" at random from the pile
 *
 * Selects a character with a weighted random selection based on char frequency
 * Decrements the frequency of the selected character
 */
char pile::draw() {
    if (pileMap.empty()) {
        return ' ';
    }
    // generate weighted keyset
    vector<char> keyset;
    for (auto it : pileMap) {
        for (int i = 0; i < it.second; i++) {
            keyset.push_back(it.first);
        }
    }
    int idx = (int) (rand() % keyset.size());
    char ch = keyset[idx];
    int freq = pileMap.at(ch);
    if (freq <= 1) {
        pileMap.erase(ch);
    } else {
        pileMap[ch]--;
    }
    return ch;
}

/*
 * @param ch A character to put back in the pile
 * @return a new character
 *
 * Draws a character from the pile and then adds the input character back to the pile
 */
char pile::replace(char ch) {
    char result = draw();
    pileMap.at(ch)++;
    return result;
}