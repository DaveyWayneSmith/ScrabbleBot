//
// Created by Edward on 6/15/2016.
//

using namespace std;
#include <dawg-builder.h>
#include <dictionary.h>
#include <dictionary-builder.h>
#include <cstring>
#include <fstream>
#include "myDictionary.h"
#include "definitions.h"

myDictionary::myDictionary() {
    std::ifstream file;
    file.open(DAVEY_DICT_FILE.c_str());
    if (!file) {
        file.open(PI_DICT_FILE.c_str());
    }
    if (!file) {
        file.open(ED_DICT_FILE.c_str());
    }
    std::string line;
    while (getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); // clean the line
        slow_dict.insert(line);
    }
}

bool myDictionary::exactLookup(std::string word) {
    // return dict.Contains(word.c_str());
    return slow_dict.find(word) != slow_dict.end();
}

set<string> myDictionary::partialLookup(string key, unsigned long start, bool exact) {
    set<string> result;
    for (auto s = slow_dict.begin(); s != slow_dict.end(); ++s) {
        string str = *s;
        size_t idx = str.find(key, start);
        if (idx != string::npos && (exact ? idx == start : true)) {
            result.insert(str);
        }
    }
    return result;
}

set<string> myDictionary::partialLookup(string key) {
    partialLookup(key, 1, false);
}