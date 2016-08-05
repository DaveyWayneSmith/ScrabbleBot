#include <iostream>
#include "game.h"
#include <wiringPi.h>

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
	bool UP = true;
	bool DN = false;
	ArmController controller = ArmController();
	//cout << "basic test\n";
	//controller.moveTile(UP);
	//controller.moveArm(point{0, 0}, point{2, 5});
	//controller.moveTile(DN);
	//controller.moveArm(point{2, 5}, point{0, 0});

	// cout << "medium test\n";
	//for (int i = 0; i < 10; i++) {
	//	cout << "Run #: " << i << "\n";
    //    controller.resetX();
    //    controller.resetY();
	//	controller.moveTile(UP);
	//	controller.moveArm(point{0, 0}, point{17, 15});
	//	controller.moveTile(DN);
	//	controller.moveArm(point{17, 15}, point{0, 0});
	//	cout << "Safely exit now..." << flush;
	//	delay(3000);
	//	cout << "Cannot safely exit now\n";
	//}
	// cout << "hard test\n";
	// for (int i = 1; i < 14; i++) {
	//	cout << "Run #: " << i << "\n";
	//	controller.moveTile(UP);
	//	controller.moveArm(point{0, 0}, point{i, i});
	//	controller.moveTile(DN);
	//	controller.moveArm(point{i, i}, point{0, 0});
	//	cout << "Safely exit now";
	//	delay(3000);
	//	cout << "Cannot safely exit";
	// }
        cout << "game test\n";
        controller.set("IKOECEO", placement{109, 0, "IKOECEO"});
	return 0;
    }
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

    return 0;
}

