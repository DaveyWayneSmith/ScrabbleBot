//
// Created by Edward on 6/21/2016.
//

#include "LetterRip.h"

placement LetterRip::getMove(string tray) {
    placement bestMove = placement{-1, HORZ, ""};
    int maxScore = -1;
    for (auto i : getAnchorPoints()) {
        extendLeft(i, "", "", tray, &bestMove, &maxScore);
    }
    return bestMove;
}

LetterRip::LetterRip(board* board) {
    gameBoard = board;
    dict = myDictionary();
}

vector<int> LetterRip::getAnchorPoints() {
    vector<int> anchorLocs;
    for(int i = 0; i < BOARD_SIZE; i++) {
        if (gameBoard->get(i, HORZ) == ' ' && (gameBoard->get_adj(i, 0, 'n') != ' ' || gameBoard->get_adj(i, 0, 'e') != ' ' || gameBoard->get_adj(i, 0, 's') != ' ' || gameBoard->get_adj(i, 0, 'w') != ' ')) {
            anchorLocs.push_back(i);
        }
    }
    return anchorLocs;
}

void preCompCrossWords() {

}

unsigned int LetterRip::crossCheck(int i) {
    unsigned int result = 0;

}

void LetterRip::extendLeft(int idx, string word, string placement_word, string tray, placement* maxMove, int* maxScore) {
//    extendRight(idx, idx, gameBoard->get_adj_string(idx, 0, 'w'), placement_word, tray, maxMove, maxScore);
    string copy = word;
    string copy_placement = placement_word;
    if (gameBoard->get_adj(idx, 0, 'w') != ' ') {
        extendRight(idx, idx, gameBoard->get_adj_string(idx,0,'w'), copy, tray, maxMove, maxScore);
    } else {
        string lhs = gameBoard->get_adj_string(idx, 0, 'n');
        string rhs = gameBoard->get_adj_string(idx, 0, 's');
        for (int i = 0; i < tray.size(); i++) {
            copy = word;
            copy_placement = placement_word;
            copy = tray[i] + copy;
            copy_placement = tray[i] + copy_placement;
            string new_tray = tray.substr(0, i) + tray.substr(i + 1, tray.size() - 1);
            bool crossCheck = true;
            if (lhs.size() != 0 || rhs.size() != 0) {
                string crossWord =
                        gameBoard->get_adj_string(idx, 0, 'n') + tray[i] + gameBoard->get_adj_string(idx, 0, 's');
                crossCheck = dict.exactLookup(crossWord);
            }
            if (crossCheck) {
                extendRight(idx + copy.size(), idx, copy, copy_placement, new_tray, maxMove, maxScore);
            }
        }
    }
}

void LetterRip::extendRight(int idx, int start_idx, string word, string placement_word, string tray, placement* maxMove, int* maxScore) {
    string copy = word;
    string copy_placement = placement_word;
    if (gameBoard->get(idx, HORZ) != ' ') {
        copy += gameBoard->get(idx, HORZ);
        if (dict.prefixExists(copy)) { // cross check is always true
            copy_placement += "_";
            extendRight(idx + 1, start_idx, copy, copy_placement, tray, maxMove, maxScore);
        }
        if (dict.exactLookup(copy)) { // we could stop here and have a valid move
            int end = (int) copy_placement.size() - 1;
            placement_word = copy_placement.at(end) == '_' ? copy_placement.erase(end) : copy_placement;
            placement test_placement = placement{start_idx, HORZ, copy_placement};
            int test_score = gameBoard->calcScore(test_placement);
            if (test_score > *maxScore) {
                *maxScore = test_score;
                *maxMove = test_placement;
            }
        }
    } else {
        string lhs = gameBoard->get_adj_string(idx, 0, 'n');
        string rhs = gameBoard->get_adj_string(idx, 0, 's');
        for (int i = 0; i < tray.size(); i++) {
            copy = word;
            copy_placement = placement_word;
            copy += tray[i];
            copy_placement += tray[i];
            bool crossCheck = true;
            if (lhs.size() != 0 || rhs.size() != 0) {
                string crossWord =
                        gameBoard->get_adj_string(idx, 0, 'n') + tray[i] + gameBoard->get_adj_string(idx, 0, 's');
                crossCheck = dict.exactLookup(crossWord);
            }
            placement test_placement = placement{start_idx, HORZ, copy_placement};
            if (gameBoard->checkBounds(test_placement) && crossCheck) {
                if (dict.prefixExists(copy)) {
                    string new_tray = tray.substr(0, i) + tray.substr(i + 1, tray.size() - 1);
                    extendRight(idx + 1, start_idx, copy, copy_placement, new_tray, maxMove, maxScore);
                }
                if (dict.exactLookup(copy)) { // we could stop here and have a valid move
                    int test_score = gameBoard->calcScore(test_placement);
                    if (test_score > *maxScore) {
                        *maxScore = test_score;
                        *maxMove = test_placement;
                    }
                }
            }
        }
    }
}