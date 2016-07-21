//
// Created by Edward on 7/14/2016.
//

#ifndef SCRABBLEBOT_ARMCONTROLLER_H
#define SCRABBLEBOT_ARMCONTROLLER_H

using namespace std;
#include <string>
#include "definitions.h"

typedef struct cartPair {
    double x;
    double y;
} cartPair;

class ArmController {
public:
    void set(string tray, placement move);
private:
    cartPair home = cartPair{0, 0}; // the home position of the arm
    cartPair trayAnchor = cartPair{0, 0}; // the point from which tray offsets will be calculated
    cartPair boardAnchor = cartPair{0, 0}; // the point from which all board offsets will be calculated
    cartPair tileSize = cartPair{0, 0}; // the size of a tile

    cartPair trayIdx2point(int idx); // convert a tray string index into an [x, y] cartPair
    cartPair boardIdx2point(int idx); // convert a board index to an [x, y] cartPair
    cartPair distance(cartPair start, cartPair end); // compute the x and y distance between two points
};


#endif //SCRABBLEBOT_ARMCONTROLLER_H
