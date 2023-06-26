#ifndef TRIE_H
#define TRIE_H
#include "TrieNode.h"
#include "isEndOfWord.h"
#include <string>


#include <iostream>



using namespace std;
class Trie {
    public:
        TrieNode* root;
        Trie() {
            root = new TrieNode();
        }

        void insertWord(string& str, int& line, int isFirst) {
            TrieNode* curr = root;
            for (char c: str) {
                if(curr->children.find(c) == curr->children.end()) {
                    curr->children[c] = new TrieNode();
                }
                curr = curr->children[c];
            }
            if(isFirst == 1) curr->isEndOfWord.frequency[line] = 0;
            curr->isEndOfWord.frequency[line]++;
            curr->isEndOfWord.line.insert(line);
        }

        struct IsEndOfWord searchWord(string& str) {
            TrieNode* curr = root;         
            struct IsEndOfWord wrongAns;
            wrongAns.line = {};
            for (char c: str) {
                if(curr->children.find(c) == curr->children.end()) {
                    return wrongAns;
                }
                curr = curr->children[c];
            }
            return curr->isEndOfWord;
        }
};

#endif