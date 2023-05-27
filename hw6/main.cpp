#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cmath>
#include <vector>
#include "Trie.h"
#include "TrieNode.h"
#include "printSet.h"
#include "insertCorpus.h"
#include "IdfRank.h"
using namespace std;

inline double IDF(int, int);
bool cmp(int, int);

int main(int argc, char** argv) {
    fstream corpus(argv[1]);
    fstream query(argv[2]);
    int num, numOfCorpus = 0;
    string sentence, strNum, findSentence;
    Trie corpusTrie = Trie();
    
    
    while(getline(corpus, strNum, ',')) {
        getline(corpus, sentence, '\n');
        //divide corpus and submit to Trie
        num = stoi(strNum);
        insertCorpus(num, sentence, &corpusTrie);
        numOfCorpus++;
    }

    map<int, int> ans; // the number of line, idf sum
    //ans.reserve(numOfCorpus);

    while(getline(query, findSentence, '\n')) {
        string word;
        istringstream ss(findSentence);
        int IDFvalue, frequency = 0;

        while(ss >> word) {
            frequency = corpusTrie.searchWord(word).size();
            IDFvalue = IDF(numOfCorpus, frequency);
            for(int a: corpusTrie.searchWord(word)) {
                if(ans.find(a) == ans.end()) {
                    ans[a] = 0;
                }else {
                    ans[a] += IDFvalue;
                }
            }
        }

        vector<pair<int, int>> ansRank(ans.begin(), ans.end());
        sort(ansRank.begin(), ansRank.end(), cmp);

        cout << ansRank[0].first << " " << ansRank[1].first << " " << ansRank[2].first;
        
    }

    
        
}

inline double IDF(int numberOfCorpus, int frequency) {
    return log((double)numberOfCorpus/frequency);
}