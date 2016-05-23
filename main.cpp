#include <iostream>
#include <vector>
#include "pile.h"
#include "game.h"

const int TRAY_SIZE = 7;

using namespace std;
vector<char> playerOneRack;
vector<char> playerTwoRack;
pile* testPile = new pile();

int main() {
//    game* mainGame = new game();
//    mainGame.start();
    board testBoard = board();
    testBoard.display();
    testBoard.place(0, 0, "HELLO");
    cout << testBoard.calcScore(0,0,"HELLO") << "\n";
    testBoard.place(15, 1, "WORLD");
    cout << testBoard.calcScore(15,1,"WORLD") << "\n";
    testBoard.display();
    return 0;
}

