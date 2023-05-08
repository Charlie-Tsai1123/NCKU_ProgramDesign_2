#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "Trie.h"
#include "TrieNode.h"
#include "printSet.h"
#include "insertCorpus.h"
using namespace std;

int main(int argc, char** argv) {
    fstream corpus(argv[1]);
    fstream query(argv[2]);
    int num;
    string sentence, strNum;
    Trie corpusTrie;
    
    
    while(getline(corpus, strNum, ',')) {
        getline(corpus, sentence, '\n');
        //divide corpus and submit to Trie
        insertCorpus(stoi(strNum), sentence, corpusTrie);
    }
    

    
    while(getline(query, sentence, '\n')) {
        string word;
        istringstream ss(sentence);
        set<int> firstWord;
        
        //the first
        ss >> word;
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); });
        firstWord = corpusTrie.searchWord(word);
        if(firstWord.empty()) {
            cout << "-1" << endl;
            continue;
        }

        //the second
        
        //the second doesn't exist
        if(!(ss >> word)) {
            printSet(firstWord);
            continue;
        }
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); });
        set<int> secondWord = corpusTrie.searchWord(word);
        //not found secondword in corpus
        if(secondWord.empty()) {
            cout << "-1" << endl;
            continue;
        }
        //found second word in corpus
        set<int>result2;
        set_intersection(firstWord.begin(), firstWord.end(),
                        secondWord.begin(), secondWord.end(),
                        inserter(result2, result2.begin()));

        //the third

        //the third word doesn't exist
        if(!(ss >> word)) {
            printSet(result2);
            continue;
        }
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); });
        set<int> thirdWord = corpusTrie.searchWord(word);
        if(thirdWord.empty()) {
            cout << "-1" << endl;
            continue;
        }
        set<int>result3;
        set_intersection(result2.begin(), result2.end(),
                        thirdWord.begin(), thirdWord.end(),
                        inserter(result3, result3.begin()));
        printSet(result3);
    }
}
