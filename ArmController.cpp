//
// Created by Edward on 7/14/2016.
//

#include <algorithm>
#include "ArmController.h"

void ArmController::set(string tray, placement move) {
    for (auto c : move.word) {
        if (c == '_' || c == ' ') {
            continue;
        }
        auto idx = tray.find(c);
        if (idx == string::npos) {
            c = '*';
            idx = tray.find(c);
        }

    }

}

cartPair ArmController::boardIdx2point(int idx) {
    int x = idx % BOARD_SIDE_LEN;
    int y = idx / BOARD_SIDE_LEN;
    return cartPair{boardAnchor.x + x, boardAnchor.y + y};
}

/*
 * Assumes that the letters are arranged vertically from 0 to 6 with trayAnchor pointing to the middle of tray[0]
 */
cartPair ArmController::trayIdx2point(int idx) {
    return cartPair{trayAnchor.x, trayAnchor.y + idx * tileSize.y};
}

cartPair ArmController::distance(cartPair start, cartPair end) {
    return cartPair{end.x - start.x, end.y - start.y};
}