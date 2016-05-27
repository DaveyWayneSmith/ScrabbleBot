//
// Created by Edward on 5/19/2016.
//

#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include "game.h"

void game::start() {
    int maxscore = 0;
    display();
    bool first = true;
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

        // perform first time check to see if word crosses the center
        if (first) {
            first = false;
            if (dir == HORZ && (loc > CENTER || loc + word.length() < CENTER)) {
                loc = -1;
                first = true;
            }
            else if (dir == VERT) {
                // transposing the starting index
                int r = loc / BOARD_SIDE_LEN;
                int c = loc % BOARD_SIDE_LEN;
                int trans_idx = c * BOARD_SIDE_LEN + r;
                if (trans_idx > CENTER || trans_idx + word.length() < CENTER) {
                    loc = -1;
                    first = true;
                }
            }
        }

        int score = play(placement{loc, dir, word});
        players[currPlayer].score += score;
        currPlayer = ++currPlayer % numPlayers;
        display();
    }
}

int game::play(placement move) {
    int score = 0;
    int cross_loc[move.word.length()] = {0};
    if (validate(move, cross_loc)) {
        score = gameBoard.place(move);
        // check for intersections
        // if intersection found, replace with '_'
        for (int i = 0; i < move.word.length(); i++) {
            if (cross_loc[i]) {
                move.word[i] = '_';
            }
        }
        // replace used characters
        for (int i = 0; i < move.word.length(); i++) {
            if (strchr(players[currPlayer].tray.c_str(), move.word[i])) {
                char ch = tilePile.draw();
                for (int j = 0; j < players[currPlayer].tray.length(); j++) {
                    if (move.word[i] == players[currPlayer].tray[j]) {
                        players[currPlayer].tray[j] = ch;
                        break;
                    }
                }

            }
        }
    }
    return score;
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

bool game::validate(placement move, int* cross_loc) {
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
        int obds_val = (move.loc / BOARD_SIDE_LEN + 1) * BOARD_SIDE_LEN;
        if (move.loc + move.word.length() > obds_val) return false;
    } else {
        int r = move.loc / BOARD_SIDE_LEN;
        int c = move.loc % BOARD_SIDE_LEN;
        int trans_idx = c * BOARD_SIDE_LEN + r;
        int obds_val = (trans_idx / BOARD_SIDE_LEN + 1) * BOARD_SIDE_LEN;
        if (trans_idx + move.word.length() > obds_val) return false;
    }
    // at this point we are guaranteed that the word can physically fit on the board

    // now check if the letters are in the tray
    for (int i = 0; i < move.word.length(); i++) {
        //first check if tray contains the current letter
        // if not, then check if the board at that locations contains the letter
        if (!strchr(players[currPlayer].tray.c_str(), move.word[i]) &&
                    move.word[i] != gameBoard.get((short) (move.loc + i * (move.dir == HORZ ? 1 : BOARD_SIDE_LEN)))) {
            return false;
        } else if (strchr(players[currPlayer].tray.c_str(), move.word[i]) &&
                    move.word[i] == gameBoard.get((short) (move.loc + i * (move.dir == HORZ ? 1 : BOARD_SIDE_LEN)))) {
            cross_loc[i] = 1;
        }
    }
    // now check if word is in dictionary
    ifstream file;
    file.open(ED_DICT_FILE);
    if (!file) {
        file.open(DAVEY_DICT_FILE);
    }
    string line;
    bool found = false;
    while (getline(file, line) && !found) {
        found = (bool) strcmp(line.c_str(), move.word.c_str());
    }
    if (!found) return false;

    // still need to perform cross checks
    return true;
}

