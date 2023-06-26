#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>
#include <set>
#include "isEndOfWord.h"
using namespace std;

class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        struct IsEndOfWord isEndOfWord;
        TrieNode () {
        }
};

#endif