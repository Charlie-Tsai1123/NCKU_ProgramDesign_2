#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>
#include "Trie.h"
#include "TrieNode.h"
#include "printSet.h"
using namespace std;

int main(int argc, char** argv) {
    fstream corpus(argv[1]);
    fstream query(argv[2]);
    int num;
    string sentence;
    Trie corpusTrie;
    while(getline(corpus, sentence, '\n')) {
        char* sep = " ,\"'.?!()";
        char* token = strtok(sentence.c_str, sep);
        num = stoi(token);
        token = strtok(NULL, sep);
        while(token != NULL) {
            transform(token, token+strlen(token), token, tolower);
            corpusTrie.insertWord(token, num);
            token = strtok(NULL, sep);
        }
    }

    
    while(getline(query, sentence, '\n')) {
        //the first query
        char* token = strtok(sentence.c_str, ' ');
        transform(token, token+strlen(token), token, tolower);
        string strToken(token);
        set<int> word1 = corpusTrie.searchWord(strToken);
        //first query doesn't in corpus
        if(a1.empty()) {
            cout << "-1 " << endl;
            continue;
        }

        //the second query
        token = strtok(NULL, ' ');
        //no second query -> print word1
        if(token == NULL) {
            printSet(word1);
            continue;
        }

        transform(token, token+strlen(token), token, tolower);
        strToken(token);
        set<int> word2 = corpusTrie.searchWord(strToken);
        //second query doesn't in corpus
        if(word2.empty()) {
            cout << "-1 " << endl;
            continue;
        }

        //the third query
        set<int> result;
        set_intersection(word1.begin(), word1.end(),
                         word2.begin(), word2.end(),
                         inserter(result, result.begin()));
        //no third query
        token = strtok(NULL, ' ');
        if(token == NULL) {
            printSet(result);
            continue;
        }

        transform(token, token+strlen(token), token, tolower);
        strToken(token);
        set<int> word3 = corpusTrie.searchWord(strToken);
        //third query doesn't in corpus
        if(word3.empty()) {
            cout << "-1 " << endl;
            continue;
        }

        set_intersection(result.begin(), result.end(),
                         word3.begin(), word3.end(),
                         inserter(result, result.begin()));
        printSet(result);
    }
}