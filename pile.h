#ifndef SCRABBLEBOT_PILE_H
#define SCRABBLEBOT_PILE_H

using namespace std;
#include <map>

class pile {
    map<char, int> pileMap;
public:
    pile(); // constructor
    char draw(); // draw method
};

#endif //SCRABBLEBOT_PILE_H