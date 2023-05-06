#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>
#include <set>
using namespace std;

class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        set<int> isEndOfWord;
};

#endif