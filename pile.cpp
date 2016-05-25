//
// Created by Davey Smith on 5/17/16.
//

#include <vector>
#include <time.h>
#include <cstdlib>
#include "pile.h"

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

char pile::draw() {
    if (pileMap.empty()) {
        return NULL;
    }
    // generate weighted keyset
    vector<char> keyset;
    for (auto it : pileMap) {
        for (int i = 0; i < it.second; i++) {
            keyset.push_back(it.first);
        }
    }
    int idx = rand() % keyset.size();
    char ch = keyset[idx];
    int freq = pileMap.at(ch);
    if (freq <= 1) {
        pileMap.erase(ch);
    } else {
        pileMap[ch]--;
    }
    return ch;
}
