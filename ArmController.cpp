//
// Created by Edward on 7/14/2016.
//

#include <algorithm>
#include "ArmController.h"
#include <wiringPi.h>
#include <iostream>

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

void ArmController::set(player p, placement move) {
    if (!p.ai) return;
    string tray = p.tray;
    cout << "The AI tray is: " << tray << "\nPress any key when AI tray is ready.";
    char temp;
    cin >> temp;
    int board_loc = TRANSPOSE(move.loc, move.dir);
	cout << "initial location: " << board_loc << "\n";
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
        tray[idx] = '_';
	point next = trayIdx2point(idx);
	cout << "tray x: " << next.x << "\n";
	cout << "tray y: " << next.y << "\n";
	moveArm(home);
	resetX();
	resetY();
        moveArm(trayIdx2point(idx)); // go to the tile
        moveTile(UP);
	next = boardIdx2point(TRANSPOSE(board_loc, move.dir));
	cout << "board x: " << next.x << "\n";
	cout << "board y: " << next.y << "\n";
	cout << "board idx: " << (TRANSPOSE(board_loc, move.dir)) << "\n";
        moveArm(boardIdx2point(TRANSPOSE(board_loc, move.dir))); // move to the final location
	cout << "curr x: " << curr.x << "\n";
	cout << "curr y: " << curr.y << "\n";
        moveTile(DN);
	board_loc++;
    }
    moveArm(home);
    resetX();
    resetY();
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

void ArmController::moveArm(point stop) {
    int deltaX = stop.x - curr.x;
    int deltaY = stop.y - curr.y;
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
    int x = idx / BOARD_SIDE_LEN + boardAnchor.x;
    int y = idx % BOARD_SIDE_LEN + boardAnchor.y;
    return point{x, y};
}

/*
 * Assumes that the letters are arranged vertically from 0 to 6 with trayAnchor pointing to the middle of tray[0]
 */
point ArmController::trayIdx2point(int idx) {
    return point{trayAnchor.x, trayAnchor.y + idx};
}

void ArmController::resetX() {
    digitalWrite(X0, LOW);
    digitalWrite(X1, HIGH);
    digitalWrite(XE, HIGH);
    delay(X_RESET_TIME);
    digitalWrite(XE, LOW);
}

void ArmController::resetY() {
	cout << "resetting y pos\n";
    digitalWrite(Y0, HIGH);
    digitalWrite(Y1, LOW);
    digitalWrite(YE, HIGH);
    delay(Y_RESET_TIME);
    digitalWrite(YE, LOW);
}