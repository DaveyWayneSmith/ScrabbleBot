//
// Created by Edward on 5/19/2016.
//

#include <iostream>
#include <cstring>
#include "game.h"

void game::start() {
    int maxscore = 0;
    display();
    while (maxscore < SCORE_CAP) {
        for (auto p:players) {
            if (p.score > maxscore) {
                maxscore = p.score;
            }
        }
        short loc;
        cout << "Enter a starting location:\n";
        cin >> loc;

        short dir;
        cout << "Enter a direction (HORZ = 0 | VERT = 1):\n";
        cin >> dir;

        string word;
        cout << "Enter your word:\n";
        cin >> word;
        int score = play(placement{loc, dir, word});
        players[currPlayer].score += score;
        currPlayer = ++currPlayer % numPlayers;
        display();
    }
}

int game::play(placement move) {
    if (validate(move)) {
        return gameBoard.place(move);
    }
    return -1;
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

bool game::validate(placement move) {
    if (move.loc < 0 || move.loc > 255) {
        return false;
    }
    if (move.dir < 0 || move.dir > 1) {
        return false;
    }
    if (move.word.length() > 15) {
        return false;
    }
    // at this point we are guaranteed a 0 <= loc <= 255 and word.length() <= 15
    if (move.dir == HORZ) {
        if (move.loc + move.word.length() > (move.loc + move.word.length()) / BOARD_SIDE_LEN * BOARD_SIDE_LEN) { // if the word goes off the board
            return false;
        }
    } else {
        // perform the vertical version of the out of bounds check
    }
    // at this point we are guaranteed that the word can physically fit on the board

    // now check if word is in dictionary
    FILE* fh = fopen(DICT_FILE, "r");
    while (!feof(fh)) {
        string line = fgets(fh);
        if (strcmp(line, move.word)) {
            break;
        }
    }
    if (!feof(fh)) { // if we got to the end of the file without finding the word
        return false;
    }
    fclose(fh);
    // still need to perform cross checks
    return true;
}

