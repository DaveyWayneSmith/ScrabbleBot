#include <iostream>
#include "game.h"
#include <vector>



using namespace std;

int main() {
    game* mainGame = new game();
//    mainGame->start();

    placement p1 = placement{110, 0, "ABACTERIAL"};
    placement p2 = placement{89, 1, "BA_E"};

    vector<placement> p1_ext = mainGame->extend(p1);
    bool p1_check = mainGame->validate(p1, &p1_ext);
    int p1_score = mainGame->play(p1);

    vector<placement> p2_ext = mainGame->extend(p2);
    bool p2_check = mainGame->validate(p2, &p2_ext);
    int p2_score = mainGame->play(p2);


    mainGame->display();
    return 0;
}

