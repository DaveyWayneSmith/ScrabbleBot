//
// Created by Davey Smith on 5/17/16.
//

#include "pile.h"

pile::pile() {
    pileMap.insert(pair<char, int>('A', 9));
    pileMap.insert(pair<char, int>('B', 2));
    pileMap.insert(pair<char, int>('C', 2));
    pileMap.insert(pair<char, int>('D', 4));
    pileMap.insert(pair<char, int>('E', 12));
    pileMap.insert(pair<char, int>('F', 2));
    pileMap.insert(pair<char, int>('G', 3));
    pileMap.insert(pair<char, int>('H', 2));
    pileMap.insert(pair<char, int>('I', 9));
    pileMap.insert(pair<char, int>('J', 1));
    pileMap.insert(pair<char, int>('K', 1));
    pileMap.insert(pair<char, int>('L', 4));
    pileMap.insert(pair<char, int>('M', 2));
    pileMap.insert(pair<char, int>('N', 6));
    pileMap.insert(pair<char, int>('O', 8));
    pileMap.insert(pair<char, int>('P', 2));
    pileMap.insert(pair<char, int>('Q', 1));
    pileMap.insert(pair<char, int>('R', 6));
    pileMap.insert(pair<char, int>('S', 4));
    pileMap.insert(pair<char, int>('T', 6));
    pileMap.insert(pair<char, int>('U', 4));
    pileMap.insert(pair<char, int>('V', 2));
    pileMap.insert(pair<char, int>('W', 2));
    pileMap.insert(pair<char, int>('X', 1));
    pileMap.insert(pair<char, int>('Y', 2));
    pileMap.insert(pair<char, int>('Z', 1));
    pileMap.insert(pair<char, int>('*', 2));

}

char pile::draw() {
    char ch = rand() % 27;
    int freq;
    if (ch == 26) { // we are dealing with a wildcard
        ch = '*';
    } else {
        ch += 'A';
    }
    freq = pileMap.at(ch);
    if (freq == 0) {
        return draw();
    } else {
        //pileMap[ch]--; // need to work on this
        return ch;
    }
}
