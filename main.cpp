#include <iostream>
#include "pile.h"

using namespace std;
char board[15][15];
char playerOneRack[7];
char playerTwoRack[7];
pile* testPile = new pile();

int onStart() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            board[i][j] = ' ';
        }
    }
    for (int j = 0; j < 7; j++) {
        playerOneRack[j] = testPile->draw();
        playerTwoRack[j] = testPile->draw();
    }
    return 0;
};

int main() {
    onStart();
    for (int i = 0; i < 102; i++) {
        char ch = testPile->draw();
        cout << ch;
    }
    return 0;
}

