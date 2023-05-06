#include "check.h"

bool cmpMax(MaxContinue, MaxContinue);
void check (vector<Staff> staff) {
    //initialize max array, currentMax, check current;
    MaxContinue max[3];
    for(int i=0; i<3; i++) max[i] = MaxContinue(0, 0, "", "");

    MaxContinue currentMax = MaxContinue(staff[0].employeeId, 0, "", "");

    MaxContinue current = MaxContinue(staff[0].employeeId, 0, staff[0].strTime, "");

    time_t currentTime;
    struct tm initialCurrentTime = {0};
    initialCurrentTime.tm_year = staff[0].time.tm_year;
    initialCurrentTime.tm_mon = staff[0].time.tm_mon;
    initialCurrentTime.tm_mday = staff[0].time.tm_mday;
    currentTime = mktime(&initialCurrentTime) - 86400;

    for(auto &v: staff) {
        //calculate check_time
        struct tm staffTime = {0};
        staffTime.tm_year = v.time.tm_year;
        staffTime.tm_mon = v.time.tm_mon;
        staffTime.tm_mday = v.time.tm_mday;
        time_t staffTimeSec = mktime(&staffTime);

        //employeeId different
        if(v.employeeId != current.employeeId) {
            if(current.continueDay >= currentMax.continueDay) {
                currentMax.continueDay = current.continueDay;
                currentMax.initialTime = current.initialTime;
                currentMax.finalTime = current.finalTime;
            }
            if(cmpMax(currentMax, max[2])) {
                max[2] = currentMax;
                sort(max, max+3, cmpMax);
                //cout << "$$" << max[0].employeeId << "," << max[1].employeeId << "," << max[2].employeeId << endl;
            }
            current.employeeId = v.employeeId;
            current.continueDay = 1;
            current.initialTime = v.strTime;
            current.finalTime = v.strTime;

            currentMax.employeeId = v.employeeId;
            currentMax.continueDay = 0;

            currentTime = staffTimeSec;

            continue;
        }

        //employeeId the same
        double diffTime = difftime(staffTimeSec, currentTime);
        int diffDay = diffTime/(60*60*24);
    
        if(diffDay == 1) {
            current.continueDay++;
            current.finalTime = v.strTime;
        }else if(diffDay == 0) {
            current.finalTime = v.strTime;
        }else {
            if(current.continueDay >= currentMax.continueDay) {
                currentMax.continueDay = current.continueDay;
                currentMax.initialTime = current.initialTime;
                currentMax.finalTime = current.finalTime;
            }
            current.continueDay = 1;
            current.initialTime = v.strTime;
            current.finalTime = v.strTime;
        }
        currentTime = staffTimeSec;
    }

    if(current.continueDay >= currentMax.continueDay) {
        currentMax.continueDay = current.continueDay;
        currentMax.initialTime = current.initialTime;
        currentMax.finalTime = current.finalTime;
    }
    if(cmpMax(currentMax, max[2])) {
        max[2] = currentMax;
        sort(max, max+3, cmpMax);
        //cout << "$$" << max[0].employeeId << "," << max[1].employeeId << "," << max[2].employeeId << endl;
    }

    //print max
    for(auto &v: max){
        cout << v.employeeId << "," << v.continueDay << ",";
        for(int i=0; i<8; i++) {
            cout << v.initialTime[i];
        }
        cout << ",";
        for(int i=0; i<8; i++) {
            cout << v.finalTime[i];
        }
        cout << endl;
    }
}

bool cmpMax(MaxContinue x, MaxContinue y) {
    if(x.continueDay != y.continueDay) return x.continueDay > y.continueDay;
    return x.employeeId < y.employeeId;
}