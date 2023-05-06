#include "check.h"

bool cmpMax(pair<Staff, int>, pair<Staff, int>);
void check(vector<Staff> staff) {
    //initialize max, current
    pair<Staff, int> max[3];
    pair<Staff, int> current;
    pair<Staff, int> currentMax;
    max[0] = make_pair(Staff(0, 0, "000000000000"), 0);
    max[1] = make_pair(Staff(0, 0, "000000000000"), 0);
    max[2] = make_pair(Staff(0, 0, "000000000000"), 0);
    current = make_pair(Staff(staff[0].employeeId, 0, "000000000000"), 1);
    currentMax = make_pair(Staff(staff[0].employeeId, 0, "000000000000"), 1);

    //start check
    for(auto &v: staff) {
        //id 不同
        if(currentMax.first.employeeId != v.employeeId) {
            if(cmpMax(currentMax, max[2])) {
                max[2].first = Staff(currentMax.first.employeeId, currentMax.first.sign, currentMax.first.strTime);
                max[2].second = currentMax.second;
                sort(max, max+3, cmpMax);
            }
            current.first = Staff(v.employeeId, v.sign, v.strTime);
            current.second = 1;
            currentMax.first = Staff(v.employeeId, 0, "000000000000");
            currentMax.second = 0;
            continue;
        }

        //id相同
        bool result = checkContinue(current, v);
        if(result) {
            current.second++;
            current.first = Staff(v.employeeId, v.sign, v.strTime);
        }else {
            if(cmpMax(current, currentMax)) {
                currentMax.first = Staff(current.first.employeeId, current.first.sign, current.first.strTime);
                currentMax.second = current.second;
            }
            current.first = Staff(v.employeeId, v.sign, v.strTime);
            current.second = 1;
        }
    }

    cout << max[0].first.employeeId << "," << max[0].second << "," << max[0].first.strTime << endl;
    cout << max[0].first.employeeId << "," << max[1].second << "," << max[0].first.strTime << endl;
    cout << max[0].first.employeeId << "," << max[2].second << "," << max[0].first.strTime << endl;
    
}
bool cmpMax(pair<Staff, int> a, pair<Staff, int> b){
    if(a.second != b.second) return a.second > b.second;
    if(a.first.employeeId != b.first.employeeId) return a.first.employeeId < b.first.employeeId;
    if(a.first.time.year != b.first.time.year) return a.first.time.year > b.first.time.year;
    if(a.first.time.month != b.first.time.month) return a.first.time.month > b.first.time.month;
    return a.first.time.day > b.first.time.day;
}
