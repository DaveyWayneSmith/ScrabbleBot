//
// Created by Edward on 6/15/2016.
//

#ifndef SCRABBLEBOT_DICTIONARY_H
#define SCRABBLEBOT_DICTIONARY_H


#include <set>
#include "trie.h"

class myDictionary {
    set<string> slow_dict;
    trie_t theTrie;
public:
    myDictionary();
    set<string> partialLookup(string key); //find all words that contain 'key'
    set<string> partialLookup(string key, unsigned long start, bool exact); //only find matches where the key is found at or after a given index
                                                                               //if exact is specified as true, only matches that start exactly at 'start' will be considered
    bool exactLookup(string word); // lookup a full word
    bool partialExists(string key); // lookup if a substring exists anywhere in the dictionary
    bool prefixExists(string key); // lookup if a substring exists at the beginning of any word

};


#endif //SCRABBLEBOT_DICTIONARY_H
