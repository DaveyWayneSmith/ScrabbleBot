//
// Created by Edward on 7/14/2016.
//

#include <algorithm>
#include "ArmController.h"
#include <wiringPi.h>

ArmController::ArmController() {
    wiringPiSetupGpio();
    pinMode(MOTOR_X_ENPIN, OUTPUT);
    pinMode(MOTOR_X_0PIN, OUTPUT);
    pinMode(MOTOR_X_1PIN, OUTPUT);

    pinMode(MOTOR_Y_ENPIN, OUTPUT);
    pinMode(MOTOR_Y_0PIN, OUTPUT);
    pinMode(MOTOR_Y_1PIN, OUTPUT);

    pinMode(MOTOR_Z_ENPIN, OUTPUT);
    pinMode(MOTOR_Z_0PIN, OUTPUT);
    pinMode(MOTOR_Z_1PIN, OUTPUT);

    pinMode(VAC_ENPIN, OUTPUT);
    pinMode(VAC_0PIN, OUTPUT);
    pinMode(VAC_1PIN, OUTPUT);

    // set vacuum pins here so only have to worry about enable later
    digitalWrite(VAC_0PIN, HIGH); // TODO may have to switch this
    digitalWrite(VAC_1PIN, LOW);
}

void ArmController::set(string tray, placement move) {
    int board_loc = TRANSPOSE(move.loc, move.dir);
    for (auto c : move.word) {
        if (c == '_' || c == ' ') {
            board_loc++;
            continue;
        }
        auto idx = tray.find(c);
        if (idx == string::npos) {
            c = '*';
            idx = tray.find(c);
        }
        moveArm(curr, trayIdx2point(idx)); // go to the tile
        toggleVac(); // turn the vacuum on
        toggleVert(); // move down to the tile
        delay(wait);
        toggleVert(); // go back up
        delay(wait);
        moveArm(curr, boardIdx2point(TRANSPOSE(board_loc, move.dir))); // move to the final location
        delay(wait);
        toggleVert(); // move down to the board
        delay(wait);
        toggleVac(); // release the tile
        delay(wait);
        toggleVert(); // move back up
    }
    moveArm(curr, home);
}

void ArmController::toggleVac() {
    if (vacOn) {
        digitalWrite(VAC_ENPIN, LOW);
        vacOn = false;
    } else {
        digitalWrite(VAC_ENPIN, HIGH);
        vacOn = true;
    }
}
void ArmController::toggleVert() {
    if (!vertLoc) { // if the arm is UP, move it down
        digitalWrite(MOTOR_Z_0PIN, HIGH); //TODO may have to switch these pins to get the arm to go the right way
        digitalWrite(MOTOR_Z_1PIN, LOW);
    } else { // otherwise the arm must be down so move it up
        digitalWrite(MOTOR_Z_0PIN, LOW);
        digitalWrite(MOTOR_Z_1PIN, HIGH);
    }
    digitalWrite(MOTOR_Z_ENPIN, HIGH);
    delay(VERT_DIST);
    digitalWrite(MOTOR_Z_ENPIN, LOW);
    vertLoc = !vertLoc;
}

void ArmController::moveArm(cartPair start, cartPair stop) {
    int deltaX = stop.x - start.x;
    int deltaY = stop.y - start.y;
    if (deltaX > 0) {
        digitalWrite(MOTOR_X_0PIN, LOW); // TODO may have to switch this
        digitalWrite(MOTOR_X_1PIN, HIGH);
    } else {
        digitalWrite(MOTOR_X_0PIN, HIGH);
        digitalWrite(MOTOR_X_1PIN, LOW);
    }

    if (deltaY > 0) {
        digitalWrite(MOTOR_Y_0PIN, LOW); // TODO may have to switch this
        digitalWrite(MOTOR_Y_1PIN, HIGH);
    } else {
        digitalWrite(MOTOR_Y_0PIN, HIGH);
        digitalWrite(MOTOR_Y_1PIN, LOW);
    }
    int absX = abs(deltaX);
    int absY = abs(deltaY);
    digitalWrite(MOTOR_X_ENPIN, HIGH);
    delay(absX);
    digitalWrite(MOTOR_X_ENPIN, LOW);
    digitalWrite(MOTOR_Y_ENPIN, HIGH);
    delay(absY);
    digitalWrite(MOTOR_Y_ENPIN, LOW);
    curr = stop;
}

cartPair ArmController::boardIdx2point(int idx) {
    int x = idx % BOARD_SIDE_LEN;
    int y = idx / BOARD_SIDE_LEN;
    return cartPair{boardAnchor.x + x * TILE_X_WIDTH, boardAnchor.y + y * TILE_Y_WIDTH};
}

/*
 * Assumes that the letters are arranged vertically from 0 to 6 with trayAnchor pointing to the middle of tray[0]
 */
cartPair ArmController::trayIdx2point(int idx) {
    return cartPair{trayAnchor.x, trayAnchor.y + idx * TILE_Y_WIDTH};
}