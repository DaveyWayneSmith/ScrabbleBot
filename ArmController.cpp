//
// Created by Edward on 7/14/2016.
//

#include <algorithm>
#include "ArmController.h"
#include <wiringPi.h>

ArmController::ArmController() {
    wiringPiSetupGpio();
    pinMode(XE, OUTPUT);
    pinMode(X0, OUTPUT);
    pinMode(X1, OUTPUT);

    pinMode(YE, OUTPUT);
    pinMode(X0, OUTPUT);
    pinMode(Y1, OUTPUT);

    pinMode(ZE, OUTPUT);
    pinMode(Z0, OUTPUT);
    pinMode(Z1, OUTPUT);

    pinMode(VE, OUTPUT);
    pinMode(V0, OUTPUT);
    pinMode(V1, OUTPUT);

    // set vacuum pins here so only have to worry about enable later
    digitalWrite(V0, HIGH); // TODO may have to switch this
    digitalWrite(V1, LOW);
}

void ArmController::set(string tray, placement move) {
    int board_loc = TRANSPOSE(move.loc, move.dir);
    for (auto c : move.word) {
        if (c == '_' || c == ' ') {
            board_loc++;
            continue;
        }
        int idx = (int) tray.find(c);
        if (idx == string::npos) {
            c = '*';
            idx = (int) tray.find(c);
        }
        moveArm(curr, trayIdx2point(idx)); // go to the tile
        moveTile(UP);
        moveArm(curr, boardIdx2point(TRANSPOSE(board_loc, move.dir))); // move to the final location
        moveTile(DN);
    }
    moveArm(curr, home);
}

void ArmController::moveTile(bool dir) {
    delay(PAUSE_TIME);
    if (dir) { // if picking a tile up
        vacSwitch(ON);
    }
    //go down
    digitalWrite(Z0, HIGH); //TODO may have to switch these pins to get the arm to go the right way
    digitalWrite(Z1, LOW);
    digitalWrite(ZE, HIGH);
    delay(VERT_DIST);
    digitalWrite(ZE, LOW);

    if (!dir) { // moving a tile down
        vacSwitch(OFF);
    }
    delay(300); // wait to suck up/release tile

    //go up
    digitalWrite(Z0, LOW);
    digitalWrite(Z1, HIGH);
    digitalWrite(ZE, HIGH);
    delay(VERT_DIST);
    digitalWrite(ZE, LOW);
    delay(PAUSE_TIME);
}

void ArmController::moveArm(point start, point stop) {
    int deltaX = stop.x - start.x;
    int deltaY = stop.y - start.y;
    int x_width;
    int y_width;
    if (deltaX > 0) {
        digitalWrite(X0, HIGH);
        digitalWrite(X1, LOW);
	x_width = TILE_X_POS_WIDTH;
    } else {
        digitalWrite(X0, LOW);
        digitalWrite(X1, HIGH);
	x_width = TILE_X_NEG_WIDTH;
    }

    if (deltaY > 0) {
        digitalWrite(Y0, LOW);
        digitalWrite(Y1, HIGH);
	y_width = TILE_Y_POS_WIDTH;
    } else {
        digitalWrite(Y0, HIGH);
        digitalWrite(Y1, LOW);
	y_width = TILE_Y_NEG_WIDTH;
    }
    unsigned int absX = (unsigned int) abs(deltaX);
    unsigned int absY = (unsigned int) abs(deltaY);
    digitalWrite(XE, HIGH);
    delay(absX * x_width);
    digitalWrite(XE, LOW);
    digitalWrite(YE, HIGH);
    delay(absY * y_width);
    digitalWrite(YE, LOW);
    curr = stop;
}

void ArmController::vacSwitch(bool which) {
    delay(PAUSE_TIME);
    if (which) { // switch vacuum on
        digitalWrite(VE, HIGH);
    } else {
        digitalWrite(VE, LOW);


    }
    delay(PAUSE_TIME);
}

point ArmController::boardIdx2point(int idx) {
    int x = idx % BOARD_SIDE_LEN + boardAnchor.x;
    int y = idx / BOARD_SIDE_LEN + boardAnchor.y;
    return point{x, y};
}

/*
 * Assumes that the letters are arranged vertically from 0 to 6 with trayAnchor pointing to the middle of tray[0]
 */
point ArmController::trayIdx2point(int idx) {
    return point{trayAnchor.x, trayAnchor.y + idx};
}