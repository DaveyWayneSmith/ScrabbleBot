//
// Created by Edward on 7/14/2016.
//

#ifndef SCRABBLEBOT_ARMCONTROLLER_H
#define SCRABBLEBOT_ARMCONTROLLER_H

using namespace std;
#include <string>
#include "definitions.h"

typedef struct cartPair {
    int x;
    int y;
} cartPair;

class ArmController {
public:
    ArmController();
    void set(string tray, placement move);
private:
    static const int wait = 50; // number of ms to wait between each arm action
    static const bool UP = false;
    static const bool DN = true;

    static const int TILE_X_WIDTH = 0;
    static const int TILE_Y_WIDTH = 0;
    static const int VERT_DIST = 0;

    static const int MOTOR_X_ENPIN = 0;
    static const int MOTOR_X_0PIN = 0;
    static const int MOTOR_X_1PIN = 0;

    static const int MOTOR_Y_ENPIN = 0;
    static const int MOTOR_Y_0PIN = 0;
    static const int MOTOR_Y_1PIN = 0;

    static const int MOTOR_Z_ENPIN = 0;
    static const int MOTOR_Z_0PIN = 0;
    static const int MOTOR_Z_1PIN = 0;

    static const int VAC_ENPIN = 0;
    static const int VAC_0PIN = 0;
    static const int VAC_1PIN = 0;

    cartPair home = cartPair{0, 0}; // the home position of the arm
    cartPair curr = home;
    bool vertLoc = UP;
    bool vacOn = false;

    cartPair trayAnchor = cartPair{0, 0}; // the point from which tray offsets will be calculated
    cartPair boardAnchor = cartPair{0, 0}; // the point from which all board offsets will be calculated

    cartPair trayIdx2point(int idx); // convert a tray string index into an [x, y] cartPair
    cartPair boardIdx2point(int idx); // convert a board index to an [x, y] cartPair
    cartPair distance(cartPair start, cartPair end); // compute the x and y distance between two points
    void moveArm(cartPair start, cartPair stop);
    void toggleVert();
    void toggleVac();
};


#endif //SCRABBLEBOT_ARMCONTROLLER_H
