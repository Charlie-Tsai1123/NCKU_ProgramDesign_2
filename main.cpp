#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "Trie.h"
#include "TrieNode.h"
#include "printSet.h"
using namespace std;

void to_lower(char* str) {
    for(int i=0; i<strlen(str); i++) {
        if(str[i] > 'z') str[i] = str[i] - 'A' + 'a';
    }
}

int main(int argc, char** argv) {
    fstream corpus(argv[1]);
    fstream query(argv[2]);
    int num;
    string sentence;
    Trie corpusTrie;
    
    while(getline(corpus, sentence, '\n')) {


        cout << "###" << sentence << endl;


        char* charSentence = new char[sentence.length() + 1];
        char* sep = " ,\"'.?!()";
        strcpy(charSentence, sentence.c_str());
        char* token = strtok(charSentence, sep);
        num = stoi(token);

        cout << num << endl;

        
        token = strtok(NULL, sep);
        while(token != NULL) {
            to_lower(token);
            

            cout << "***" << token << endl;


            corpusTrie.insertWord(token, num);
            token = strtok(NULL, sep);
        }
        delete[] charSentence;
    }
    

    
    while(getline(query, sentence, '\n')) {
        char* charSentence1 = new char[sentence.length() + 1];
        //the first query
        strcpy(charSentence1, sentence.c_str());
        char* token = strtok(charSentence1, " ");
        to_lower(token);
        string strToken(token);


        cout << "&&&" << strToken << endl;

        
        set<int> word1 = corpusTrie.searchWord(strToken);
        //first query doesn't in corpus
        if(word1.empty()) {
            cout << "-1 " << endl;
            continue;
        }

        //the second query
        token = strtok(NULL, " ");
        //no second query -> print word1
        if(token == NULL) {
            printSet(word1);
            continue;
        }

        to_lower(token);
        strToken = token;
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
        token = strtok(NULL, " ");
        if(token == NULL) {
            printSet(result);
            continue;
        }

        to_lower(token);
        strToken = token;
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
        delete[] charSentence1;
    }
    
    
}