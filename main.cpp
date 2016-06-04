#include <iostream>
#include "game.h"
#include <vector>



using namespace std;

int main() {
    game* mainGame = new game();
//    mainGame->start();

    placement p1 = placement{112, 0, "ABACTERIAL"};
    placement p2 = placement{112, 0, "AB"};
    placement p3 = placement{98, 1, "A_A"};
    placement p4 = placement{126, 0, "ABCX"};
    placement p5 = placement{126, 0, "ABCXY"};

    vector<placement> p1_ext = mainGame->extend(p1);
    bool p1_check = mainGame->validate(p1, p1_ext);
    mainGame->play(p1);

    vector<placement> p2_ext = mainGame->extend(p2);
    bool p2_check = mainGame->validate(p2, p2_ext);
    mainGame->play(p2);

    vector<placement> p3_ext = mainGame->extend(p3);
    bool p3_check = mainGame->validate(p3, p3_ext);
    mainGame->play(p3);

    vector<placement> p4_ext = mainGame->extend(p4);
    bool p4_check = mainGame->validate(p4, p4_ext);
    mainGame->play(p4);

    vector<placement> p5_ext = mainGame->extend(p5);
    bool p5_check = mainGame->validate(p5, p5_ext);
    mainGame->play(p5);


    mainGame->display();
    return 0;
}

