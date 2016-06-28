//
// Created by Edward on 6/27/2016.
//

#include <fstream>
#include "DictTrie.h"
#include "definitions.h"
#include <algorithm>

DictTrie::DictTrie() {
    root = new TrieNode();
    // try to add words from the 3 possible input files
    std::ifstream file;
    file.open(DAVEY_DICT_FILE.c_str());
    if (!file) {
        file.open(PI_DICT_FILE.c_str());
    }
    if (!file) {
        file.open(ED_DICT_FILE.c_str());
    }
    string curWord;
    while (getline(file, curWord)) {
        curWord.erase(std::remove(curWord.begin(), curWord.end(), '\r'), curWord.end());
        insert(curWord);
    }
    file.close();
}

DictTrie::~DictTrie(){ }

bool DictTrie::containsPrefix(string str) {
    return root->containsPrefix(root, str);
}

bool DictTrie::containsWord(string str) {
    return root->containsWord(root, str);
}

void DictTrie::insert(string str) {
    root->put(root, str);
}