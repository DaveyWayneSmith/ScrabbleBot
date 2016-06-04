//
// Created by Edward on 5/22/2016.
//

#ifndef SCRABBLEBOT_DEFINITIONS_H
#define SCRABBLEBOT_DEFINITIONS_H

#define TRANSPOSE(loc) (((loc) % 15) * 15 + ((loc) / 15))

static const int VERT = 1;
static const int HORZ = 0;

static const int DL = 0;
static const int TL = 1;
static const int DW = 2;
static const int TW = 3;

static const int BOARD_SIZE = 225;
static const int BOARD_SIDE_LEN = 15;
static const int CENTER = 112;
static const int TRAY_SIZE = 7;

static const int SCORE_CAP = 50;

static const string ED_DICT_FILE = "C:\\Users\\Edward\\Documents\\ScrabbleBot\\dictionary.txt";
static const string DAVEY_DICT_FILE = "dictionary.txt";

typedef struct placement {
    short loc;
    short dir;
    string word;
} placement;

#endif //SCRABBLEBOT_DEFINITIONS_H
