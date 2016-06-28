#include <iostream>
#include "game.h"

using namespace std;

int main() {
    DictTrie dict = DictTrie();
    bool a = dict.containsWord("APPLE");
    bool b = dict.containsPrefix("PL");

    int num_players = 0;
    do {
        cout << "How many players are there?\n";
        cin >> num_players;
    } while (num_players < 2 || num_players > 4);

    vector<bool> playerType = vector<bool>((unsigned long) num_players);
    char human;
    bool cont;
    for (int i = 0; i < playerType.size(); i++) {
        cont = true;
        do {
            fprintf(stdout, "Player %d: R U Hooman? (y/n)?\n", i + 1);
            cin >> human;
            if (human == 'n') {
                playerType[i] = true;
                cont = false;
            } else if (human == 'y') {
                cont = false;
            }
        } while (cont);
    }

    game* mainGame = new game(playerType);
    mainGame->start();

//    board gameBoard = board();
//    LetterRip ai = LetterRip(&gameBoard);
//    gameBoard.place(placement{37, VERT, "TYPEWRITER"});
//    gameBoard.place(placement{98, HORZ, "HISTLE"});
//    gameBoard.place(placement{140, HORZ, "LE_TER"});
//    gameBoard.place(placement{170, HORZ, "NO_TH"});
////    gameBoard.place(placement{110, VERT, "CA_E_DAR"});
//    gameBoard.display();
////    placement testPlacement;
////    int maxScore;
//
////    ai.extendLeft(214,"","","XAETSRI",&testPlacement,&maxScore);
////    cout << testPlacement.word;
////    cout << "\n";
////    cout << maxScore;
////    cout << "\n";
////
////    maxScore = -1;
////
////    ai.extendLeft(216,"","","XAETSRI",&testPlacement,&maxScore);
////    cout << testPlacement.word;
////    cout << "\n";
////    cout << maxScore;
////    cout << "\n";
//    gameBoard.place(ai.getMove("XAETSRI"));
//
//    gameBoard.display();

    return 0;
}

