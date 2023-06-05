#ifndef TRIE_H
#define TRIE_H
#include "TrieNode.h"
#include <string>
#include <iostream>



using namespace std;
class Trie {
    public:
        TrieNode* root;
        Trie() {
            root = new TrieNode();
        }

        void insertWord(string& str, int& line) {
            TrieNode* curr = root;
            for (char c: str) {
                if(curr->children.find(c) == curr->children.end()) {
                    curr->children[c] = new TrieNode();
                }
                curr = curr->children[c];
            }
            //isEndOfWord -> set
            //curr->isEndOfWord.insert(line);

            //isEndOfWord -> map
            if(curr->isEndOfWord.find(line) == curr->isEndOfWord.end()) curr->isEndOfWord[line] = 0;
            else curr->isEndOfWord[line]++;
        }

        map<int, int> searchWord(string& str) {
            TrieNode* curr = root;         
            map<int, int> wrongAns;
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