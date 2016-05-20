#include <iostream>
#include <vector>
#include "pile.h"

using namespace std;
char board[15][15];
vector<char> playerOneRack;
vector<char> playerTwoRack;
pile* testPile = new pile();

int onStart() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            board[i][j] = ' ';
        }
    }
    for (int j = 0; j < 7; j++) {
        playerOneRack.push_back(testPile->draw());
        playerTwoRack.push_back(testPile->draw());
    }
    return 0;
};

int main() {
    onStart();

    return 0;
}

