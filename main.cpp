#include <iostream>
#include "game.h"
#include <stdio.h>
#include <wiringPi.h>
#define	LED 0

using namespace std;

int main(int argc, char** argv) {
    	if (argc > 1) {
        // testing code here
	printf ("Raspberry Pi blink\n") ;

  	wiringPiSetup () ;
  	pinMode (LED, OUTPUT) ;

  	for (;;) {
    		digitalWrite (LED, HIGH) ;	// On
    		delay (500) ;		// mS
    		digitalWrite (LED, LOW) ;	// Off
    		delay (500) ;
  	}
        board testBoard = board();
        DictTrie dict = DictTrie();
        LetterRip testAI = LetterRip(&testBoard, &dict);
        testBoard.place(placement{24, HORZ, "CURULE"});
        testBoard.place(placement{11, VERT, "ORCEIN"});
        testBoard.display();
        int val1 = testBoard.calcScore(placement{106, HORZ, "QWER__TYU"}, false);
        int val2 = testBoard.calcScore(placement{121, HORZ, "Q_W_E_R_T_Y"}, false);
        int val3 = testBoard.calcScore(placement{136, HORZ, "QWERTYU"}, false);
        placement move = testAI.getMove("AX");
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

