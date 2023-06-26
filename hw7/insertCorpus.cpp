#include "insertCorpus.h"

int insertCorpus(int& line, string &str, Trie *corpusTrie) {
    int allOfWord = 0;
    map<string, int> check;
    string word;
    for (char c: str) {
        if(isalpha(c)) {
            word += c;
        }else if(c == ' ' && !word.empty()) {
            allOfWord++;
            transform(word.begin(), word.end(), word.begin(), [](unsigned char t){ return tolower(t); });
            if(check.find(word) == check.end()) {
                check[word] = 1;
                corpusTrie->insertWord(word, line, 1);
            }else {
                corpusTrie->insertWord(word, line, 0);
            }
            
            word.clear();
        }
    }
    if(!word.empty()){
        allOfWord++;
        transform(word.begin(), word.end(), word.begin(), [](unsigned char t){return tolower(t); });
        if(check.find(word) == check.end()) {
            check[word] = 1;
            corpusTrie->insertWord(word, line, 1);
        }else {
            corpusTrie->insertWord(word, line, 0);
        }
        word.clear();
    }
    return allOfWord;
}