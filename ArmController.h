//
// Created by Edward on 7/14/2016.
//

#ifndef SCRABBLEBOT_ARMCONTROLLER_H
#define SCRABBLEBOT_ARMCONTROLLER_H

using namespace std;
#include <string>
#include "definitions.h"

typedef struct point {
    int x;
    int y;
} point;

/*
 * Notes on dealing with hardware:
 * Arm is assumed to be in home position with arm in raised position and the vacuum off when this class is initialized.
 * If anything goes wrong with the mechanics of the arm, there is little change of recovery
 * If the design of any of the mechanics is changed, the time constants will need to be changed
 * If the wiring of the motors/vacuum is changed, the pin numbers will need to be changed
 *
 * All methods that control physical components are bookended by a pause of PAUSE_TIME (in ms)
 */
class ArmController {
public:
    ArmController();
    void set(string tray, placement move);

    // TODO these methods only public for debugging
    point trayIdx2point(int idx); // convert a tray string index into an [x, y] point
    point boardIdx2point(int idx); // convert a board index to an [x, y] point
    void moveTile(bool dir); // move a tile up or down
    void moveArm(point start, point stop);
    void vacSwitch(bool which); // turn the vacuum on or off
private:
    static const bool UP = true;
    static const bool DN = false;

    static const bool ON = true;
    static const bool OFF = false;

    //time constants
    static const int TILE_X_POS_WIDTH = 7600 / BOARD_SIDE_LEN;
    static const int TILE_X_NEG_WIDTH = 8000 / BOARD_SIDE_LEN;
    static const int TILE_Y_POS_WIDTH = 3000 / BOARD_SIDE_LEN;
    static const int TILE_Y_NEG_WIDTH = 2800 / BOARD_SIDE_LEN;
    static const int VERT_DIST = 500;
    static const int PAUSE_TIME = 100;

    // pin numbers
    static const int XE = 4; // motor x enable pin
    static const int X0 = 13; // motor x 0 pin
    static const int X1 = 16; // motor x 1 pin

    static const int YE = 5; // motor y enable pin
    static const int Y0 = 17; // motor y 0 pin
    static const int Y1 = 18; // motor y 1 pin

    static const int ZE = 6; // motor z enable pin
    static const int Z0 = 22; // motor z 0 pin
    static const int Z1 = 23; // motor z 1 pin

    static const int VE = 12; // vacuum enable pin
    static const int V0 = 24; // vacuum 0 pin
    static const int V1 = 25; // vacuum 1 pin

    point home = point{0, 0}; // the home position of the arm from which all offsets will be calculated (should be {0, 0})
    point curr = home; // arm is assumed to be in home position when initialized

    point trayAnchor = point{0, 0}; // the point (in ms) from which tray offsets will be calculated
    point boardAnchor = point{0, 0}; // the point (in ms) from which all board offsets will be calculated
};


#endif //SCRABBLEBOT_ARMCONTROLLER_H
