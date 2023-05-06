#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <utility>
using namespace std;
#include "Staff.h"
#include "check.h"
#include "Time.h"

bool cmp(Staff, Staff);

int main(int argc, char** argv) {
    ifstream file(argv[1]);
    if(!file.is_open()) {
        cerr << "wrong!" << endl;
        return 1;
    }

    //Input
    vector<Staff> staff;
    string str;
    int employeeId1, sign1, timeYear1, timeMonth1, timeDay1, time1;
    while(getline(file, str, ',')) {
        employeeId1 = stoi(str);
        getline(file, str, ',');
        if(strcmp(str.c_str(), "sign-in") == 0) sign1 = 0;
        else sign1 = 1;
        getline(file, str);
        staff.push_back(Staff(employeeId1, sign1, str));
    }

    //排序
    sort(staff.begin(), staff.end(), cmp);

    //輸出
    check(staff);

}

bool cmp(Staff x, Staff y) {
    if(x.employeeId != y.employeeId) return x.employeeId < y.employeeId;
    if(x.time.year != y.time.year) return x.time.year < y.time.year;
    if(x.time.month != y.time.month) return x.time.month < y.time.month;
    if(x.time.day != y.time.day) return x.time.day < y.time.day;
    return x.time.time < y.time.time;
}