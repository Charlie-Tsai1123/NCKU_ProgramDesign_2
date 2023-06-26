#ifndef ISENDOFWORD_H
#define ISENDOFWORD_H
#include <map>
#include <set>
#include <utility>
using namespace std;

struct IsEndOfWord {
    set<int> line;
    map<int, int> frequency; //line, frequency
    //log(numOfCorpus(main)/line) = idf
    //frequency[line]/allOfWord[line](main) = new_tf
};

#endif