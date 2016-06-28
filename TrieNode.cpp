//
// Created by Edward on 6/27/2016.
//

#include "TrieNode.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

TrieNode::TrieNode() { }

TrieNode::~TrieNode() { }

TrieNode::TrieNode(char letter) {
    this->letter = letter;
    isWord = false;
}

bool TrieNode::containsPrefix(TrieNode* root, string str) {
    TrieNode* node = contains(root, str);
    return node != NULL;
}

bool TrieNode::containsWord(TrieNode* root, string str) {
    TrieNode* node = contains(root, str);
    if(node == NULL) {
        return false;
    }
    return node->isWord;
}

TrieNode* TrieNode::contains(TrieNode* root, string str) {
    TrieNode* node = root;
    for(unsigned int i = 0; i < str.length(); i++) {
        bool found = false;
        unsigned int charN = 0;
        while((charN < node->children.size()) && !found) {
            if(node->children.at(charN)->letter == str[i]) {
                found = true;
                node = node->children.at(charN);
            }
            charN++;
        }
        if(!found) {
            return NULL;
        }
    }
    return node;
}

void TrieNode::put(TrieNode* root, string str) {
    TrieNode* node = root;
    for(unsigned int i = 0; i < str.length(); ++i) {
        bool found = false;
        unsigned int charN = 0;
        while((charN < node->children.size()) && !found) {
            if(node->children.at(charN)->letter == str[i]) {
                node = node->children.at(charN);
                found = true;
            }
            charN++;
        }
        if(!found) {
            node->addChild(new TrieNode(str[i]));
            node = node->children.back();
        }
    }
    node->isWord = true;
}

void TrieNode::addChild(TrieNode* child) {
    children.push_back(child);
}