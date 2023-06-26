#include "insertCorpus.h"

int insertCorpus(int& line, string &str, Trie *corpusTrie) {
    int allOfWord = 0;
    string word;
    for (char c: str) {
        if(isalpha(c)) {
            word += c;
        }else if(c == ' ' && !word.empty()) {
            allOfWord++;
            transform(word.begin(), word.end(), word.begin(), [](unsigned char t){ return tolower(t); });
            corpusTrie->insertWord(word, line);
            word.clear();
        }
    }
    if(!word.empty()){
        allOfWord++;
        transform(word.begin(), word.end(), word.begin(), [](unsigned char t){return tolower(t); });
        corpusTrie->insertWord(word, line);
        word.clear();
    }
    return allOfWord;
}