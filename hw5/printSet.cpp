#include "printSet.h"

void printSet(set<int> a) {
    for(auto &s: a) {
        cout << s << " ";
    }
    cout << endl;
}