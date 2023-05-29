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
#include "insertCorpus.h"
using namespace std;

inline double IDF(int&, int&);
bool cmp(const pair<int, int>&, const pair<int, int>&);

int main(int argc, char** argv) {
    fstream corpus(argv[1]);
    fstream query(argv[2]);
    int topNum = atoi(argv[3]);

    int num, numOfCorpus = 0;
    string sentence, strNum, findSentence;
    Trie corpusTrie = Trie();
    
    //Insert Corpus
    while(getline(corpus, strNum, ',')) {
        getline(corpus, sentence, '\n');
        //divide corpus and submit to Trie
        num = stoi(strNum);
        insertCorpus(num, sentence, &corpusTrie);
        numOfCorpus++;
    }

    while(getline(query, findSentence, '\n')) {
        string word;
        istringstream ss(findSentence);
        double IDFvalue;
        int frequency = 0;
        map<int, double> ans; // the number of line, idf sum

        while(ss >> word) {
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); }); //letter tolower
            if(corpusTrie.searchWord(word).empty()) continue;
            frequency = corpusTrie.searchWord(word).size();
            IDFvalue = IDF(numOfCorpus, frequency);

            //Calculate IDFvalue of the word & Calculate the sum of IDFvalue in each line
            if (IDFvalue == 0) continue;
            for(int a: corpusTrie.searchWord(word)) {
                if(ans.find(a) == ans.end()) {
                    ans[a] = IDFvalue;
                }else {
                    ans[a] += IDFvalue;
                }
            }
        }

        //Copy map to vector because i want to sort by the value of map
        vector<pair<int, double>> ansRank(ans.begin(), ans.end());

        //*******************check vector
        /*
        for(const auto pair: ansRank) {
            cout << "&&&";
            cout << pair.first << "-->" << pair.second << endl;
        }
        */

        sort(ansRank.begin(), ansRank.end(), cmp);

        //Print the answer
        for(int i = ansRank.size(); i<topNum; i++) {
            ansRank.push_back(make_pair(-1, 0));
        }
        
        for(int i=0; i<topNum; i++) {
            if(i == 0) cout << ansRank[0].first;
            else cout << " " << ansRank[i].first; 
        }

        cout << endl;

        ans.clear();
        ansRank.clear();
       //******************
       //cout << "***************************" << endl;
    }   
}

//calculate IDF of word
inline double IDF(int& numberOfCorpus, int& frequency) {
    if(frequency == 0) return 0;
    return log((double)numberOfCorpus/frequency);
}

//compare funtion for sort vector
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}
