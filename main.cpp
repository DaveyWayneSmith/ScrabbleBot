#include <iostream>
#include <dawg-builder.h>
#include <dictionary.h>
#include <dictionary-builder.h>
#include "game.h"
#include "myDictionary.h"

using namespace std;

int main() {



    // TODO: Commented out for testing purposes
//    int num_players;
//    do {
//        cout << "How many players are there?\n";
//        cin >> num_players;
//    } while (num_players < 2 || num_players > 4);
//
//    vector<bool> playerType = vector<bool>((unsigned long) num_players);
//    char human;
//    bool cont;
//    for (int i = 0; i < playerType.size(); i++) {
//        cont = true;
//        do {
//            fprintf(stdout, "Player %d: R U Hooman? (y/n)?\n", i + 1);
//            cin >> human;
//            if (human == 'n') {
//                playerType[i] = true;
//                cont = false;
//            } else if (human == 'y') {
//                cont = false;
//            }
//        } while (cont);
//    }
//
//    game* mainGame = new game(playerType);
//    mainGame->start();

    board gameBoard = board();
    LetterRip ai = LetterRip(&gameBoard);
    gameBoard.place(placement{37, VERT, "TYPEWRITER"});
    gameBoard.place(placement{98, HORZ, "HISTLE"});
    gameBoard.place(placement{140, HORZ, "LE_TER"});
    gameBoard.place(placement{170, HORZ, "NO_TH"});
    gameBoard.place(placement{110, VERT, "CA_E_DAR"});
    gameBoard.display();
    vector<int> anchors = ai.getAnchorPoints();

    placement maxMove;
    int maxScore = -1;
    ai.extendRight(38, 38, "T", "", "XAETSRI", &maxMove, &maxScore);

    cout << maxMove.word + "\n";
    cout << maxScore + "\n";

    return 0;
}

