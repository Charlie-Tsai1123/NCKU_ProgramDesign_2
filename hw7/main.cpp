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
#include "isEndOfWord.h"
using namespace std;

inline double IDF(const int&, const int&);
inline double New_tf(int&, int&);
bool cmpIdfNew_tf(const pair<double, double>&, const pair<double, double>&);
bool cmp(const pair<int, double>&, const pair<int, double>&);

int main(int argc, char** argv) {
    fstream corpus(argv[1]);
    fstream query(argv[2]);
    int topNum = atoi(argv[3]);

    int num, numOfCorpus = 0;
    map<int, int> allOfWord; //all words in line(line, allOfWords)
    string sentence, strNum, findSentence;
    Trie corpusTrie = Trie();
    
    //Insert Corpus
    while(getline(corpus, strNum, ',')) {
        getline(corpus, sentence, '\n');
        //divide corpus and submit to Trie
        num = stoi(strNum);
        allOfWord[num] = insertCorpus(num, sentence, &corpusTrie);
        numOfCorpus++;
    }

    while(getline(query, findSentence, '\n')) {

        //^^modified^^^^^^^^^^^^^^^^
        map<int, vector<pair<double, double>>> tempAns; //line, idf, idf*new_tf;
        map<int, double> ans; // the number of line, idf*tf sum
        //^modifed^^^^^^^^^^^^^^^^^^

        string word;
        istringstream ss(findSentence);
        double IDFvalue; //^^^^^^^^
        int frequency = 0; //^^^^^^^^^^^^^^
        

        //^^^^^^^^becareful tempAns[line] may less than three cases.
        while(ss >> word) {
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return tolower(c); }); //letter tolower
            struct IsEndOfWord wordMessage = corpusTrie.searchWord(word);
            if(wordMessage.line.empty()) continue; //found nothing
            
            //calculate idf
            double idf = IDF(numOfCorpus, wordMessage.line.size());
            if(idf == 0) continue;

            //store idf and new_tf in tempAns
            for(int i: wordMessage.line) {
                double new_tf = New_tf(allOfWord[i], wordMessage.frequency[i]);
                tempAns[i].push_back(make_pair(idf, new_tf));
            }

/*
            //Calculate IDFvalue of the word & Calculate the sum of IDFvalue in each line
            for(struct IsEndOfWord a: corpusTrie.searchWord(word)) {
                if(ans.find(a) == ans.end()) {
                    ans[a] = IDFvalue;
                }else {
                    ans[a] += IDFvalue;
                }
            }
*/
        }

        for(int i=0; i<numOfCorpus+1; i++) {
            if(tempAns.find(i) == tempAns.end()) continue;
            for(int j = 0; j<3-tempAns[i].size(); j++) tempAns[i].push_back(make_pair(0, 0)); 
            sort(tempAns[i].begin(), tempAns[i].end(), cmpIdfNew_tf);
            ans[i] = 0;
            ans[i] += tempAns[i][0].second + tempAns[i][1].second + tempAns[i][2].second;
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
inline double IDF(const int& numberOfCorpus, const int& frequency) {
    if(frequency == 0) return 0;
    return log((double)numberOfCorpus/frequency);
}

//calculate new_tf of word
inline double New_tf(int &a, int &b) {
    return (double)a/b;
}

//sort function for tempAns (by 1. idf && 2. new_tf)
bool cmpIdfNew_tf(const pair<double, double>& a, const pair<double, double>& b){
    if(a.first == b.first) {
        return a.second > b.second;
    }
    return a.first > b.first;
}


//compare funtion for sort vector
bool cmp(const pair<int, double>& a, const pair<int, double>& b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}
