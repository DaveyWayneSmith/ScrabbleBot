//
// Created by Edward on 6/21/2016.
//

#include "PlayerManager.h"

PlayerManager::PlayerManager(LetterRip* AI) {
    theAI = AI;
}

placement PlayerManager::getMove(player currPlayer) {
    if (currPlayer.ai) {
        return theAI->getMove(currPlayer.tray);
    } else {
        return promptMove(currPlayer.tray);
    }
}

placement PlayerManager::promptMove(string tray) {
    fprintf(stdout, "Your tray is:\t%s\n\n", tray.c_str());
    short loc;
    cout << "Enter a starting location:\n";
    cin >> loc;

    short dir;
    cout << "Enter a direction (HORZ = 0 | VERT = 1):\n";
    cin >> dir;

    string word;
    cout << "Enter your word:\n";
    cin >> word;

    return placement{loc, dir, word};
}