//
// Created by Edward on 6/15/2016.
//

#ifndef SCRABBLEBOT_DICTIONARY_H
#define SCRABBLEBOT_DICTIONARY_H


class myDictionary {
    dawgdic::Dictionary dict;
    void filter(const dawgdic::Dictionary &dic, const char *text);
public:
    myDictionary();
    vector<string> partialLookup(string key); //find all words that contain 'key'
    vector<string> partialLookup(string key, unsigned long start, bool exact); //only find matches where the key is found at or after a given index
                                                                               //if exact is specified as true, only matches that start exactly at 'start' will be considered
    bool exactLookup(string word); // lookup a full word

};


#endif //SCRABBLEBOT_DICTIONARY_H
