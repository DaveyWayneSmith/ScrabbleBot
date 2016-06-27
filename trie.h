/*
  Simple trie data structure to play with c++11.
*/

#ifndef SCRABBLEBOT_TRIE_H_H
#define SCRABBLEBOT_TRIE_H_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "definitions.h"

typedef std::set<std::string> wordset_t;

class trie_t;

typedef std::map<char, trie_t*> child_map_t;

class trie_t {
public:
    trie_t(bool end = false) :_size(0), _isEnd(end) {}
    ~trie_t() {
        for (auto &it : _children) {
            delete it.second;
        }
    }

    void addWord(std::string word) {
        if (word.length()>0) {
            ++_size;
            std::string subword = word.substr(1, word.size()-1);
            if (_children[word[0]]) {
                _children[word[0]]->addWord(subword);
            } else {
                trie_t *tmp = new trie_t(word.size()==1);
                tmp->addWord(subword);
                _children[word[0]] = tmp;
            }
        }
    }

    bool isPrefix(std::string pref) const {
        if (pref.length()== 0) {
            return true;
        }
        if (_children.find(pref[0]) != _children.end()) {
            return _children.find(pref[0])->second->isPrefix(pref.substr(1, pref.size()-1));
        }
        return false;
    }

    bool isWord(std::string word) const {
        if (word.length()== 0) {
            return _isEnd;
        }
        std::string cursub;
        trie_t const *tmp = this;
        cursub = word;

        while (cursub.length()>0) {
            if (tmp->_children.find(cursub[0]) != tmp->_children.end()) {
                tmp = tmp->_children.find(cursub[0])->second;
                cursub = cursub.substr(1, cursub.size()-1);
            } else {
                return false;
            }
        }
        return tmp->isWordEnd();
    }

    size_t size() {
        return _size;
    }
    void getWords(wordset_t &words, std::string wordSoFar="") const {
        if (_isEnd) {
            words.insert(wordSoFar);
        }
        for (const auto &it : _children) {
            std::string tmp = wordSoFar + std::string(1, it.first);
            if (it.second && it.second->isWordEnd()) {
                words.insert(tmp);
            }
            it.second->getWords(words, tmp);
        }
    }

    void getWordsStartingWith(std::string prefix, wordset_t &words, std::string wordSoFar="") const {
        if (prefix.size() == 0) {
            getWords(words, wordSoFar);
            return;
        }
        std::string subword = prefix.substr(1, prefix.size()-1);
        if (_children.find(prefix[0]) != _children.end()) {
            trie_t *tmp = _children.find(prefix[0])->second;
            std::string nwsf = wordSoFar + std::string(1, prefix[0]);
            tmp->getWordsStartingWith(subword, words, nwsf);
        }
    }
private:
    bool isWordEnd() const {
        return _isEnd;
    }


private:
    child_map_t _children;
    size_t _size;
    bool _isEnd;
};
#endif //SCRABBLEBOT_TRIE_H_H