#include <iostream>
#include <dawg-builder.h>
#include <dictionary.h>
#include <dictionary-builder.h>
#include "game.h"
#include "myDictionary.h"

using namespace std;

int main() {
    myDictionary dict = myDictionary();
    bool a = dict.exactLookup("APPLE");
    bool b = dict.exactLookup("QQ");
    bool c = dict.exactLookup("SEVENTEEN");
    bool d = dict.exactLookup("ZOO");
    bool e = dict.exactLookup("AAA");

    set<string> test = dict.partialLookup("AB", 3, true);

    int num_players;
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
    return 0;
}

