//
// Created by Edward on 5/22/2016.
//

#ifndef SCRABBLEBOT_DEFINITIONS_H
#define SCRABBLEBOT_DEFINITIONS_H

#define TRANSPOSE(loc, dir) ((dir) ? ((loc) % 15) * 15 + ((loc) / 15) : (loc))

static const int VERT = 1;
static const int HORZ = 0;

static const int NO = 0;
static const int DL = 1;
static const int TL = 2;
static const int DW = 3;
static const int TW = 4;

static const int BOARD_SIZE = 225;
static const int BOARD_SIDE_LEN = 15;
static const int CENTER = 112;
static const int TRAY_SIZE = 7;

static const int SCORE_CAP = 500;

static const int INVALID = -1;
static const int PASS = -2;
static const int SWAP = -3;

static const string ED_DICT_FILE = "C:\\Users\\Edward\\Documents\\ScrabbleBot\\dictionary.txt";
static const string ED_VM_DICT_FILE = "/home/edward/Documents/ScrabbleBot/dictionary.txt";
static const string DAVEY_DICT_FILE = "/Users/daveysmith/ClionProjects/ScrabbleBot/dictionary.txt";
static const string PI_DICT_FILE = "/home/pi/ScrabbleBot/dictionary.txt";

typedef struct placement {
    int loc;
    int dir;
    string word;
} placement;

typedef struct player {
    int score;
    string tray;
    bool ai;
} player;

#endif //SCRABBLEBOT_DEFINITIONS_H
