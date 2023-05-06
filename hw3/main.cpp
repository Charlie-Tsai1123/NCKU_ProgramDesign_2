#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

class Staff {
    public:
        //signIn = 0, singnOut = 1; time 小時轉分鐘
        int employeeId, sign, timeYear, timeMonth, timeDay, time;
        Staff(int employeeId, int sign, int timeYear, int timeMonth, int timeDay, int time){
            this->employeeId = employeeId;
            this->sign = sign;
            this->timeYear = timeYear;
            this->timeMonth = timeMonth;
            this->timeDay = timeDay;
            this->time = time;
        };
};
bool cmp(Staff, Staff);

int main(int argc, char** argv) {
    ifstream file(argv[1]);
    if(!file.is_open()) {
        cerr << "wrong!" << endl;
        return 1;
    }

    vector<Staff> staff;
    string str;
    int employeeId1, sign1, timeYear1, timeMonth1, timeDay1, time1;
    while(getline(file, str, ',')) {
        employeeId1 = stoi(str);
        getline(file, str, ',');
        if(strcmp(str.c_str(), "sign-in") == 0) sign1 = 0;
        else sign1 = 1;
        getline(file, str);
        char timeYear[4], timeMonth[3], timeDay[3], timeHour[3], timeMin[3];
        memcpy(timeYear, str.c_str(), 4);
        memcpy(timeMonth, str.c_str()+4, 2);
        //cout << "***" << timeMonth<< endl;
        memcpy(timeDay, str.c_str()+6, 2);
        memcpy(timeHour, str.c_str()+8, 2);
        memcpy(timeMin, str.c_str()+10, 2);
        timeYear1 = atoi(timeYear);
        timeMonth1 = atoi(timeMonth);
        timeDay1 = atoi(timeDay);
        time1 = atoi(timeHour)*60 + atoi(timeMin);
        staff.push_back(Staff(employeeId1, sign1, timeYear1, timeMonth1, timeDay1, time1));
    }

    sort(staff.begin(), staff.end(), cmp);

/*
    for(auto &v: staff) {
        cout << v.employeeId << " " << v.sign << " " << v.timeYear << " " << v.timeMonth << " " << v.timeDay << " " << v.time << endl;
    }
*/

    int checkId = staff[0].employeeId, checkIn = 0, checkYear = staff[0].timeYear, checkMonth = staff[0].timeMonth, checkDay = staff[0].timeDay;
    int overloadingDays = 0, signForgetDays = 0;

    for(auto &v: staff) {
        //cout << "***" << staff[i].time << endl;
        if(checkId != v.employeeId) {
            if(checkIn != 0) signForgetDays++;
            cout << checkId << "," << overloadingDays << "," << signForgetDays << endl;
            checkId = v.employeeId;
            overloadingDays = 0;
            signForgetDays = 0;
            checkIn = 0;
            checkYear = v.timeYear;
            checkMonth = v.timeMonth;
            checkDay = v.timeDay;
        }
        
        //date difference
        if(v.timeYear != checkYear || v.timeMonth != checkMonth || v.timeDay != checkDay) {
            if(checkIn != 0) signForgetDays++;
            checkIn = 0;
            checkYear = v.timeYear;
            checkMonth = v.timeMonth;
            checkDay = v.timeDay;
        }

        //忘記sign in
        if(v.sign == 1 && checkIn == 0) {
            signForgetDays++;
            continue;
        }

        //forget sign out
        if(v.sign == 0 && checkIn != 0) {
            checkIn = v.time;
            signForgetDays++;
            continue;
        }

        //calculate
        if(v.sign == 0) {
            checkIn = v.time;
        }else if (v.time - checkIn > 480) {
            overloadingDays++;
            checkIn = 0;
        }else {
            checkIn = 0;
        }

    }

    if(checkIn != 0) signForgetDays++;
    cout << checkId << "," << overloadingDays << "," << signForgetDays << endl;
    

}

bool cmp(Staff x, Staff y) {
    if(x.employeeId != y.employeeId) return x.employeeId < y.employeeId;
    if(x.timeYear != y.timeYear) return x.timeYear < y.timeYear;
    if(x.timeMonth != y.timeMonth) return x.timeMonth < y.timeMonth;
    if(x.timeDay != y.timeDay) return x.timeDay < y.timeDay;
    return x.time < y.time;
}