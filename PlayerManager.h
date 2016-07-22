//
// Created by Edward on 6/21/2016.
//

#ifndef SCRABBLEBOT_PLAYERMANAGER_H
#define SCRABBLEBOT_PLAYERMANAGER_H

using namespace std;
#include <iostream>
#include "LetterRip.h"
#include "definitions.h"
//#include "ArmController.h"

class PlayerManager {
public:
    PlayerManager(LetterRip* AI); // constructor
    placement getMove(player currPlayer); //get a move from the player

private:
    LetterRip* theAI;
//    ArmController controller = ArmController();
    placement promptMove(string tray); // go though terminal prompts to get a human move
};


#endif //SCRABBLEBOT_PLAYERMANAGER_H
