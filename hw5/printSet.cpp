#include "printSet.h"

void printSet(set<int>& a) { 
    auto s = a.begin();
    for(; s != prev(a.end()); s++) { 
        cout << *s << " ";
    }
    cout << *s << endl;
}