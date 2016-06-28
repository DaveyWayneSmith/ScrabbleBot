//
// Created by Edward on 6/27/2016.
//

#ifndef SCRABBLEBOT_TRIENODE_H
#define SCRABBLEBOT_TRIENODE_H

#include <vector>
#include <string>

class TrieNode {
public:
    TrieNode();
    virtual ~TrieNode();
    TrieNode(char letter);
    void put(TrieNode* root, std::string str);
    bool containsWord(TrieNode* root, std::string str);
    bool containsPrefix(TrieNode* root, std::string str);

private:
    char letter;
    bool isWord;
    std::vector<TrieNode*> children;
    void addChild(TrieNode* child);
    TrieNode* contains(TrieNode* root, std::string str);
};


#endif //SCRABBLEBOT_TRIENODE_H
