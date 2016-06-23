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
    void partialLookup(string key);
    bool exactLookup(std::string word); // lookup a full word

};


#endif //SCRABBLEBOT_DICTIONARY_H
