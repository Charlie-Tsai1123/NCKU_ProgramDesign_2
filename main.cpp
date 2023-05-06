#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <Trie.h>
#include <TrieNode.h>
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
        tokne = strtok(NULL, sep);
        while(token != NULL) {
            corpusTrie.insertWord(token, num);
            token = strtok(NULL, sep);
        }
    }

    
    while(getline(query, sentence, '\n')) {
        int noElement = 0;
        char* token = strtok(sentence.c_str, ' ');
        vector<int> a1 = corpusTrie.searchWord(token);
        if(a1.empty()) {
            cout << "-1 " << endl;
            continue;
        }

        token = strtok(NULL, ' ');
        if(token == NULL) {



        }
        vector<int> a2 = corpusTrie.searchWord(token);
        if(a2.empty()) {
            cout << "-1 " << endl;
            continue;
        }

        token = strtok(NULL, ' ');
        if(token == NULL) {


            
        }
        vector<int> a3 = corpusTrie.searchWord(token);
        if(a3.empty()) {
            cout << "-1 " << endl;
            continue;
        }

    }

    
}