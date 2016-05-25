//
// Created by Edward on 5/19/2016.
//

#include <iostream>
#include "game.h"

void game::start() {
    int maxscore = 0;
    while (maxscore < SCORE_CAP) {
        for (auto p:players) {
            if (p.score > maxscore) {
                maxscore = p.score;
            }
        }
        display();
        short loc;
        cout << "Enter a starting location:\n";
        cin >> loc;

        short dir;
        cout << "Enter a direction (HORZ = 0 | VERT = 1):\n";
        cin >> dir;

        string word;
        cout << "Enter your word:\n";
        cin >> word;
        int score = gameBoard.place(loc, dir, word);
        players[currPlayer].score += score;
        currPlayer = ++currPlayer % numPlayers;
        display();
    }
}

bool game::play() {
    return false;
}

void game::display() {
    gameBoard.display();
    for (int i = 0; i < numPlayers; i++) {
        fprintf(stdout, "Player %d Score: %d\nPlayer %d Tray: %s\n\n", i + 1, players[i].score, i + 1, players[i].tray.c_str());
    }
    fprintf(stdout, "It's currently Player %d's turn\n", currPlayer + 1);
}

game::game() {
    init(2);
}

game::game(short num) {
    init(num);
}

void game::init(short num) {
    gameBoard = board();
    tilePile = pile();
    numPlayers = num;
    players = vector<player>();
    string tray;
    for (int i = 0; i < 2; i++) {
        tray = "";
        while (tray.length() < 7) {
            tray.push_back(tilePile.draw());
        }
        players.push_back(player{0, tray});
    }
    currPlayer = 0;
}

