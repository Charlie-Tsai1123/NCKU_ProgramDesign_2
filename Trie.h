#ifndefTRIE_H
#define TRIE_H
#include "TrieNode.h"
#include <string>
using namespace std;
class Trie {
    public:
        TrieNode* root;
        Trie() {
            root = new TrieNode();
        }

        void insertWord(string str, int line) {
            TrieNode* curr = root;
            for (char c: str) {
                if(curr->children.find(c) == curr->children.end()) {
                    curr->children[c] = new TrieNode();
                }
                curr = curr->children[c];
            }
            curr->isEndOfWord.push_back(line);
        }

        vector<int> searchWord(string str) {
            TrieNode* curr = root;
            vector<int> wrongAns;
            for (char c: str) {
                if(curr->children.find(c) == curr->children.end()) {
                    return wrongAns;
                }
                curr = curr->children[c]
            }
            return curr->isEndOfWord;
        }
};

#endif