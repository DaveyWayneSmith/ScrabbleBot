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
                int trans_idx = TRANSPOSE(loc);
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
    int cross_score = validate(move, cross_loc);
    if (cross_score != -1) {
        score = gameBoard.place(move);
        score += cross_score;
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

int game::validate(placement move, int* cross_loc) {
    if (move.loc < 0 || move.loc > 255) {
        return -1;
    }
    if (move.dir < 0 || move.dir > 1) {
        return -1;
    }
    if (move.word.length() > 15) {
        return -1;
    }
    // at this point we are guaranteed a 0 <= loc <= 255 and word.length() <= 15
    int norm_idx = move.dir ? TRANSPOSE(move.loc) : move.loc;
    int obds_val = (norm_idx / BOARD_SIDE_LEN + 1) * BOARD_SIDE_LEN;
    if (norm_idx + move.word.length() > obds_val) return -1;
    // at this point we are guaranteed that the word can physically fit on the board

    // now check if the letters are in the tray
    for (int i = 0; i < move.word.length(); i++) {
        //first check if tray contains the current letter
        // if not, then check if the board at that locations contains the letter
        if (!strchr(players[currPlayer].tray.c_str(), move.word[i]) &&
                    move.word[i] != gameBoard.get((short) (move.loc + i * (move.dir == HORZ ? 1 : BOARD_SIDE_LEN)))) {
            return -1;
        } else if (strchr(players[currPlayer].tray.c_str(), move.word[i]) &&
                    move.word[i] == gameBoard.get((short) (move.loc + i * (move.dir == HORZ ? 1 : BOARD_SIDE_LEN)))) {
            cross_loc[i] = 1;
        }
    }
    // now check if word is in dictionary
    if (!dictCheck(move.word)) return -1;
    // finally, perform cross checks
    return crossCheck(move);
}

int game::crossCheck(placement move) {
    int loc = move.loc;
    int dir = move.dir;
    string word = move.word;
    int cross_score = 0;
    bool adj_flag = gameBoard.isempty();
    int norm_loc;
    int ch_loc;
    for (int i = 0; i < word.length(); i++) {
        norm_loc = dir ? TRANSPOSE(loc) : loc;
        // if this is the start of a word and it's not on the left edge, then check preceding space
        if (i == 0 && norm_loc % BOARD_SIDE_LEN != 0 && gameBoard.get(norm_loc - 1, dir) != ' ') {
            return -1;
        }
        // if this is the end of the word and it is not on the right edge, check following space
        if (i == word.length() - 1 && (norm_loc + word.length()) % BOARD_SIDE_LEN != (BOARD_SIDE_LEN - 1)
                && gameBoard.get(loc + word.length(), dir) != ' ') {
            return -1;
        }
        string ext_str;
        int ext_start_loc = norm_loc;
        ext_str += word.at(i);
        // extend upward
        int ext_idx = norm_loc + i - 15;
        while (ext_idx >= 0 && gameBoard.get(ext_idx, dir) != ' ') {
            ext_str = gameBoard.get(ext_idx, dir) + ext_str;
            ext_start_loc = ext_idx;
            ext_idx -= 15;
        }
        // extend downward
        ext_idx = norm_loc + i + 15;
        while (ext_idx < BOARD_SIZE && gameBoard.get(ext_idx, dir) != ' ') {
            ext_str += gameBoard.get(ext_idx, dir);
            ext_idx += 15;
        }
        if (ext_str.length() > 1 && !dictCheck(ext_str)) {
            return -1;
        } else if (ext_str.length() > 1) {
            cross_score += gameBoard.calcScore(placement{dir ? TRANSPOSE(ext_start_loc) : ext_start_loc, dir ? HORZ : VERT, ext_str});
        }
        ch_loc = norm_loc + i;
        if (gameBoard.get_adj(ch_loc, dir, 'n') != ' ' || gameBoard.get_adj(ch_loc, dir, 's') != ' ' || gameBoard.get_adj(ch_loc, dir, 'e') != ' ' || gameBoard.get_adj(ch_loc, dir, 'w') != ' ') {
            adj_flag = true;
        }
    }
    if (adj_flag) {
        return cross_score;
    } else {
        return -1;
    }
}

bool game::dictCheck(string word) {
    word += '\r';
    ifstream file;
    file.open(ED_DICT_FILE);
    if (!file) {
        file.open(DAVEY_DICT_FILE);
    }
    string line;
    bool found = false;
    while (getline(file, line) && !found) {
        found = ! (bool) strcmp(line.c_str(), word.c_str());
    }
    return found;
}
