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
//in query select top three words that have highest IDFvalue

inline double IDF(int&, int&);
bool cmpByIdfMultiplyTf(const pair<int, double>&, const pair<int, double>&);
bool cmpByIdf(const pair<string, int>&, const pair<string, int>&);

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
        vector<pair<string, int>> topIdfWord;
        map<int, double> ans; // the number of line, idf*tf sum

        //choose top three word for calculating idf*tf
        while(ss >> word) {
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); }); //letter tolower
            if(corpusTrie.searchWord(word).empty()) continue;
            frequency = corpusTrie.searchWord(word).size();
            IDFvalue = IDF(numOfCorpus, frequency);
            if (IDFvalue == 0) continue;
            topIdfWord.push_back(make_pair(word, IDFvalue));
        }

        sort(topIdfWord.begin(), topIdfWord.end(), cmpByIdf);

        //@@@@@@@@@@check if query have over three words
        if(topIdfWord.size() > 3) topIdfWord.resize(3);

        for(auto &k: topIdfWord) {
            //Calculate IDFvalue of the word & Calculate the sum of IDFvalue*tfvalue in each line
            for(auto &a: corpusTrie.searchWord(k.first)) {
                if(ans.find(a.first) == ans.end()) {
                    //a.second is tf_value
                    ans[a.first] = k.second*a.second;
                }else {
                    ans[a.first] += k.second*a.second;
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

        sort(ansRank.begin(), ansRank.end(), cmpByIdfMultiplyTf);

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
bool cmpByIdfMultiplyTf(const pair<int, double>& a, const pair<int, double>& b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

//@@@@@@@@ aware the sequence of string
bool cmpByIdf(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}