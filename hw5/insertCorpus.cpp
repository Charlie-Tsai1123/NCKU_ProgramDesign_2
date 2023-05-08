#include "insertCorpus.h"

void insertCorpus(int line, string str, Trie corpusTrie) {
    string word;
    for (char c: str) {
        if(isalpha(c)) {
            word += c;
        }else if(c == '-') {
            continue;
        }else if(!word.empty()) {
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); });
            corpusTrie.insertWord(word, line);
            word.clear();
        }
    }
}