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
    dawgdic::DawgBuilder dawg_builder;
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
        line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() ); // clean the line
        dawg_builder.Insert(line.c_str());
    }

    dawgdic::Dawg dawg;
    dawg_builder.Finish(&dawg);

    dawgdic::DictionaryBuilder::Build(dawg, &dict);
}

bool myDictionary::exactLookup(std::string word) {
    return dict.Contains(word.c_str());
}

void myDictionary::partialLookup(string key) {
    filter(dict, key.c_str());
}

void myDictionary::filter(const dawgdic::Dictionary &dic, const char *text) {

    for (const char *p = text; *p != '\0'; ++p) {

        // Begins prefix matching at each position in a text.
        dawgdic::BaseType index = dic.root();
        for (const char *q = p; *q != '\0'; ++q) {

            // Follows a transition.
            if (!dic.Follow(*q, &index))
                break;

            // Shows information of a matched key.
            // The information consists of the start position, the length,
            // the record and the string of that key.
            if (dic.has_value(index)) {
                std::cout << '(' << (p - text) << ", " << (q + 1 - p) << ", "
                << dic.value(index) << "): ";
                std::cout.write(p, q + 1 - p) << std::endl;
            }
        }
    }
}
