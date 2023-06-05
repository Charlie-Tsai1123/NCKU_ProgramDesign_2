#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>
#include <map>
using namespace std;

//use map instead of set (isEndOfWord)
class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        map<int, int> isEndOfWord; // line, tf_value(how many time appear in the line)
        TrieNode () {
        }
};

#endif