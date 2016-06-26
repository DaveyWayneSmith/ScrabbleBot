//
// Created by Edward on 6/21/2016.
//

#include "LetterRip.h"

placement LetterRip::getMove(string tray) {
    placement bestMove = placement{-1, HORZ, ""};
    int maxScore = -1;

    //TODO This is just to shut the compiler up
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

}

void LetterRip::extendRight(int idx, int start_idx, string word, string placement_word, string tray, placement* maxMove, int* maxScore) {
    if (gameBoard->get(idx, HORZ) != ' ') {
        word += gameBoard->get(idx, HORZ);
        if (dict.prefixExists(word)) { // cross check is always true
            extendRight(idx + 1, start_idx, word, placement_word + "_", tray, maxMove, maxScore);
        }
        if (dict.exactLookup(word)) { // we could stop here and have a valid move
            int end = (int) placement_word.size() - 1;
            placement_word = placement_word.at(end) == '_' ? placement_word.erase(end) : placement_word;
            placement test_placement = placement{start_idx, HORZ, placement_word};
            int test_score = gameBoard->calcScore(test_placement);
            if (test_score > *maxScore) {
                *maxScore = test_score;
                *maxMove = test_placement;
            }
        }
    } else {
        for (int i = 0; i < tray.size(); i++) {
            word += tray[i]; //TODO this might not work
            string crossWord =
                    gameBoard->get_adj_string(idx, 0, 'n') + tray[i] + gameBoard->get_adj_string(idx, 0, 's');
            bool crossCheck = dict.exactLookup(crossWord);
            if (dict.prefixExists(word) && crossCheck) {
                extendRight(idx + 1, start_idx, word, placement_word + tray[i], tray.erase(i), maxMove, maxScore);
            }
            if (dict.exactLookup(word) && crossCheck) { // we could stop here and have a valid move
                int end = (int) placement_word.size() - 1;
                placement_word = placement_word.at(end) == '_' ? placement_word.erase(end) : placement_word;
                placement test_placement = placement{start_idx, HORZ, placement_word};
                int test_score = gameBoard->calcScore(test_placement);
                if (test_score > *maxScore) {
                    *maxScore = test_score;
                    *maxMove = test_placement;
                }
            }
        }
    }
}