//
// Created by Edward on 6/21/2016.
//

#include "LetterRip.h"

placement LetterRip::getMove(string tray) {
    placement bestMove = placement{INVALID, HORZ, ""};
    int maxScore = -1;
    vector<int> anchors = getAnchorPoints();
    if (anchors.size() == 0) {
        anchors.push_back(112);
    }
    for (auto i : anchors) {
        extendLeft(i, HORZ, "", "", "", tray, &bestMove, &maxScore);
        extendLeft(TRANSPOSE(i, VERT), VERT, "", "", "", tray, &bestMove, &maxScore);
    }
    if (bestMove.loc == INVALID) {
        bestMove.loc = PASS;
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

void LetterRip::extendLeft(int idx, int trans, string word, string placement_word, string wild_loc, string tray, placement* maxMove, int* maxScore) {
    string copy_word = word;
    string copy_placement = placement_word;
    string copy_wild_loc = wild_loc;
    if (gameBoard->get_adj(idx, trans, 'w') != ' ') { // if the left part of the word is already on the board
        extendRight(idx, idx, trans, gameBoard->get_adj_string(idx, trans,'w'), copy_word, copy_word, tray, maxMove, maxScore);
    } else { // we need to generate left-parts
        if (gameBoard->get_adj(idx - 2, trans, 'w') == ' ') { // if are not about to extend into another anchor point
            // then we need to recurse on the left part
            string lhs = gameBoard->get_adj_string(idx, trans, 'n');
            string rhs = gameBoard->get_adj_string(idx, trans, 's');
            for (int i = 0; i < tray.size(); i++) {
                bool wild = tray[i] == '*';
                for (int j = 0; j < (wild ? 26 : 1); j++) {
                    char let = wild ? (char) ('A' + j) : tray[i];
                    char let_wild = wild ? '*' : tray[i];
                    // reset our working copies at the start of each new iteration
                    copy_word = word;
                    copy_placement = placement_word;
                    copy_wild_loc = wild_loc;

                    // add the current letter to the working copies
                    copy_word = let + copy_word;
                    copy_placement = let + copy_placement;
                    copy_wild_loc = let_wild + wild_loc;
                    string new_tray = tray.substr(0, i) + tray.substr(i + 1, tray.size() - 1);

                    bool crossCheck = true;
                    if (lhs.size() != 0 || rhs.size() != 0) {
                        string crossWord = gameBoard->get_adj_string(idx, trans, 'n') + let + gameBoard->get_adj_string(idx, trans, 's');
                        crossCheck = dict->containsWord(crossWord);
                    }
                    placement test_placement = placement{TRANSPOSE(idx, trans), trans, copy_wild_loc};
                    if (gameBoard->checkBounds(test_placement) && crossCheck) {
                        extendLeft(idx - 1, trans, copy_word, copy_placement, copy_wild_loc, new_tray, maxMove, maxScore);
                        extendRight((int) (idx + copy_word.size()), idx, trans, copy_word, copy_placement, copy_wild_loc, new_tray, maxMove, maxScore);
                    }

                }
            }
        }
    }
}

void LetterRip::extendRight(int idx, int start_idx, int trans, string word, string placement_word, string wild_loc, string tray, placement* maxMove, int* maxScore) {
    string copy_word = word;
    string copy_placement = placement_word;
    string copy_wild_loc = wild_loc;
    if (gameBoard->get(idx, trans) != ' ') { // if the current location contains a letter
        string ext = gameBoard->get_adj_string(idx - 1, trans, 'e');
        copy_word += ext;
        if (dict->containsPrefix(copy_word)) { // cross check is always true
            string filler = string(ext.size(), '_');
            copy_placement += filler;
            copy_wild_loc += filler;
            extendRight(idx + 1, start_idx, trans, copy_word, copy_placement, copy_wild_loc, tray, maxMove, maxScore);
        }
        if (dict->containsWord(copy_word)) { // we could stop here and have a valid move
            placement test_placement = placement{TRANSPOSE(start_idx, trans), trans, copy_wild_loc};
            int test_score = gameBoard->calcScore(test_placement, false);
            if (test_score > *maxScore) {
                *maxScore = test_score;
                *maxMove = placement{TRANSPOSE(start_idx, trans), trans, copy_placement};
            }
        }
    } else { // the current location is blank
        string lhs = gameBoard->get_adj_string(idx, trans, 'n');
        string rhs = gameBoard->get_adj_string(idx, trans, 's');
        for (int i = 0; i < tray.size(); i++) {
            bool wild = tray[i] == '*';
            for (int j = 0; j < (wild ? 26 : 1); j++) {
                char let = wild ? (char) ('A' + j) : tray[i];
                char let_wild = wild ? '*' : tray[i];
                copy_word = word;
                copy_placement = placement_word;
                copy_wild_loc = wild_loc;
                copy_word += let;
                copy_placement += let;
                copy_wild_loc += let_wild;
                bool crossCheck = true;
                if (lhs.size() != 0 || rhs.size() != 0) {
                    string crossWord = lhs + tray[i] + rhs;
                    crossCheck = dict->containsWord(crossWord);
                }
                placement test_placement = placement{TRANSPOSE(start_idx, trans), trans, copy_wild_loc};
                if (gameBoard->checkBounds(test_placement) && crossCheck) {
                    if (dict->containsPrefix(copy_word)) {
                        string new_tray = tray.substr(0, i) + tray.substr(i + 1, tray.size() - 1);
                        extendRight(idx + 1, start_idx, trans, copy_word, copy_placement, copy_wild_loc, new_tray, maxMove, maxScore);
                    }
                    if (dict->containsWord(copy_word + gameBoard->get_adj_string(idx, trans, 'e'))) { // we could stop here and have a valid move
                        int test_score = gameBoard->calcScore(test_placement, false);
                        if (test_score > *maxScore) {
                            *maxScore = test_score;
                            *maxMove = placement{TRANSPOSE(start_idx, trans), trans, copy_placement};
                        }
                    }
                }
            }
        }
    }
}