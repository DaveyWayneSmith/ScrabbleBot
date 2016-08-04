//
// Created by Edward on 6/21/2016.
//

#include "PlayerManager.h"

PlayerManager::PlayerManager(LetterRip* AI) {
    theAI = AI;
}

placement PlayerManager::getMove(player currPlayer) {
    if (currPlayer.ai) {
        cout << "AI Tray: " + currPlayer.tray + "\n";
        placement move = theAI->getMove(currPlayer.tray);
        cout << "AI start loc: " << move.loc << "\nAI dir: " << move.dir << "\nAI word: " << move.word << "\n\n";
        // controller.set(currPlayer.tray, move); // actually place the move on the board TODO do this after move verified by game
        return move;
    } else {
        return promptMove(currPlayer.tray);
    }
}

void PlayerManager::placeMove(string tray, placement move) {
    controller.set(tray, move);
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