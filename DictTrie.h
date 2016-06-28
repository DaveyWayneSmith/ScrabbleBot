//
// Created by Edward on 6/27/2016.
//

#ifndef SCRABBLEBOT_DICTTRIE_H
#define SCRABBLEBOT_DICTTRIE_H

#include <iostream>
#include <vector>
#include <bits/unique_ptr.h>
#include "TrieNode.h"

using namespace std;

class DictTrie {

public:
    DictTrie();
    virtual ~DictTrie();
    bool containsWord(std::string str);
    bool containsPrefix(std::string str);
    void insert(std::string str);

private:
    TrieNode* root;
};

#endif //SCRABBLEBOT_DICTTRIE_H
