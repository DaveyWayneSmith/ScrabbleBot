//
// Created by Edward on 6/15/2016.
//

using namespace std;
#include <dawg-builder.h>
#include <dictionary.h>
#include <cstring>
#include <fstream>
#include "myDictionary.h"

myDictionary::myDictionary() {
//    std::ifstream file;
//    file.open(DAVEY_DICT_FILE.c_str());
//    if (!file) {
//        file.open(PI_DICT_FILE.c_str());
//    }
//    if (!file) {
//        file.open(ED_DICT_FILE.c_str());
//    }
//    std::string line;
//    while (getline(file, line)) {
//        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); // clean the line
//        slow_dict.insert(line);
//    }
    std::ifstream file;
    file.open(DAVEY_DICT_FILE.c_str());
    if (!file) {
        file.open(PI_DICT_FILE.c_str());
    }
    if (!file) {
        file.open(ED_DICT_FILE.c_str());
    }
    std::string curWord;
    while (file >> curWord) {
        if (curWord.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos) {
            theTrie.addWord(curWord);
        }
    }
    file.close();
    //trie_t::buildDictionaryTrie(theTrie); // This method has been edited to attempt to cycle through the 3 possible file paths
}

bool myDictionary::exactLookup(std::string word) {
    // return dict.Contains(word.c_str());
    //return slow_dict.find(word) != slow_dict.end();

    return theTrie.isWord(word);
}

bool myDictionary::prefixExists(string key) {
//    for (auto s = slow_dict.begin(); s != slow_dict.end(); ++s) {
//        string str = *s;
//        size_t idx = str.find(key);
//        if (idx != string::npos && idx == 0) {
//            return true;
//        }
//    }
//    return false;
    return theTrie.isPrefix(key);
}