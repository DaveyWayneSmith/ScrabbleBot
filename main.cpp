#include <iostream>

using namespace std;
char board[15][15];
char playerOneRack[7];
char playerTwoRack[7];

int onStart() {
    for (int i = 0; i++; i < 15) {
        for (int j = 0; j++; j < 15) {
            board[i][j] = '';
        }
    }


    return 0;
};

int main() {
    onStart();



}

