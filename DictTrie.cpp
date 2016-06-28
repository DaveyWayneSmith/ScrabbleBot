//
// Created by Edward on 6/27/2016.
//

#include <fstream>
#include "DictTrie.h"
#include "definitions.h"

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
    while (file >> curWord) {
        curWord.erase(curWord.find_last_not_of(" \n\r\t")); // clean the line
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