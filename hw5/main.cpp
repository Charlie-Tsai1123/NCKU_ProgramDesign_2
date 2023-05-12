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
    Trie corpusTrie = Trie();
    
    
    while(getline(corpus, strNum, ',')) {
        getline(corpus, sentence, '\n');
        //divide corpus and submit to Trie
        num = stoi(strNum);
        insertCorpus(num, sentence, &corpusTrie);
    }
    
    while(getline(query, sentence, '\n')) {
        string word;
        istringstream ss(sentence);
        set<int> findQuery;
        set<int> result;
        set<int> tmp;

        ss >> word;
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {return tolower(c);});
        result = corpusTrie.searchWord(word);

        //couldn't find the first query
        if(result.empty()) {
            cout << "-1" << endl;
            continue;
        }


        bool isPrintSet = true;
        while(ss >> word) {
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); });
            findQuery = corpusTrie.searchWord(word);

            //couldn't find query
            if(findQuery.empty()) {
                isPrintSet = false;
                break;
            }

            //intersection
            tmp = result;
            result.clear();
            set_intersection(tmp.begin(), tmp.end(),
                            findQuery.begin(), findQuery.end(),
                            inserter(result, result.begin()));

            //if doesn't have the same element
            if(result.empty()) {
                isPrintSet = false;
                break;
            }
        }

        if(isPrintSet) printSet(result);
        else cout << "-1" << endl;   
    }
}
