//
// Created by Edward on 6/21/2016.
//

#include "LetterRip.h"

placement LetterRip::getMove(string tray) {
    placement bestMove = placement{-1, HORZ, ""};
    int maxScore = -1;
    for (auto i : getAnchorPoints()) {
        extendLeft(i, HORZ, "", "", tray, &bestMove, &maxScore);
        extendLeft(TRANSPOSE(i, VERT), VERT, "", "", tray, &bestMove, &maxScore);
    }
    return bestMove;
}

LetterRip::LetterRip(board* board, DictTrie* dictionary) {
    gameBoard = board;
    dict = dictionary;
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

void LetterRip::extendLeft(int idx, int trans, string word, string placement_word, string tray, placement* maxMove, int* maxScore) {
//    extendRight(idx, idx, gameBoard->get_adj_string(idx, 0, 'w'), placement_word, tray, maxMove, maxScore);
    string copy = word;
    string copy_placement = placement_word;
    if (gameBoard->get_adj(idx, trans, 'w') != ' ') {
        extendRight(idx, idx, trans, gameBoard->get_adj_string(idx, trans,'w'), copy, tray, maxMove, maxScore);
    } else {
        string lhs = gameBoard->get_adj_string(idx, trans, 'n');
        string rhs = gameBoard->get_adj_string(idx, trans, 's');
        for (int i = 0; i < tray.size(); i++) {
            copy = word;
            copy_placement = placement_word;
            copy = tray[i] + copy;
            copy_placement = tray[i] + copy_placement;
            string new_tray = tray.substr(0, i) + tray.substr(i + 1, tray.size() - 1);
            bool crossCheck = true;
            if (lhs.size() != 0 || rhs.size() != 0) {
                string crossWord =
                        gameBoard->get_adj_string(idx, trans, 'n') + tray[i] + gameBoard->get_adj_string(idx, trans, 's');
                crossCheck = dict->containsWord(crossWord);
            }
            if (crossCheck) {
                extendRight((int) (idx + copy.size()), idx, trans, copy, copy_placement, new_tray, maxMove, maxScore);
            }
        }
    }
}

void LetterRip::extendRight(int idx, int start_idx, int trans, string word, string placement_word, string tray, placement* maxMove, int* maxScore) {
    string copy = word;
    string copy_placement = placement_word;
    if (gameBoard->get(idx, HORZ) != ' ') { // if the current location contains a letter
        copy += gameBoard->get(idx, HORZ);
        if (dict->containsPrefix(copy)) { // cross check is always true
            copy_placement += "_";
            extendRight(idx + 1, start_idx, trans, copy, copy_placement, tray, maxMove, maxScore);
        }
        if (dict->containsWord(copy)) { // we could stop here and have a valid move
            auto end = copy_placement.size() - 1;
            copy_placement = copy_placement.at(end) == '_' ? copy_placement.erase(end) : copy_placement;
            placement test_placement = placement{TRANSPOSE(start_idx, trans), trans, copy_placement};
            int test_score = gameBoard->calcScore(test_placement);
            if (test_score > *maxScore) {
                *maxScore = test_score;
                *maxMove = test_placement;
            }
        }
    } else { // the current location is blank
        string lhs = gameBoard->get_adj_string(idx, trans, 'n');
        string rhs = gameBoard->get_adj_string(idx, trans, 's');
        for (int i = 0; i < tray.size(); i++) {
            copy = word;
            copy_placement = placement_word;
            copy += tray[i];
            copy_placement += tray[i];
            bool crossCheck = true;
            if (lhs.size() != 0 || rhs.size() != 0) {
                string crossWord =
                        gameBoard->get_adj_string(idx, trans, 'n') + tray[i] + gameBoard->get_adj_string(idx, trans, 's');
                crossCheck = dict->containsWord(crossWord);
            }
            placement test_placement = placement{TRANSPOSE(start_idx, trans), trans, copy_placement};
            if (gameBoard->checkBounds(test_placement) && crossCheck) {
                if (dict->containsPrefix(copy)) {
                    string new_tray = tray.substr(0, i) + tray.substr(i + 1, tray.size() - 1);
                    extendRight(idx + 1, start_idx, trans, copy, copy_placement, new_tray, maxMove, maxScore);
                }
                if (dict->containsWord(copy)) { // we could stop here and have a valid move
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