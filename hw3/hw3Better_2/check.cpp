#include "check.h"

void check (vector<Staff> staff) {
    int checkId = staff[0].employeeId, checkIn = 0, checkYear = staff[0].time.tm_year, checkMonth = staff[0].time.tm_mon, checkDay = staff[0].time.tm_mday;
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
            checkYear = v.time.tm_year;
            checkMonth = v.time.tm_mon;
            checkDay = v.time.tm_mday;
        }
        
        //date difference
        if(v.time.tm_year != checkYear || v.time.tm_mon != checkMonth || v.time.tm_mday != checkDay) {
            if(checkIn != 0) signForgetDays++;
            checkIn = 0;
            checkYear = v.time.tm_year;
            checkMonth = v.time.tm_mon;
            checkDay = v.time.tm_mday;
        }

        //忘記sign in
        if(v.sign == 1 && checkIn == 0) {
            signForgetDays++;
            continue;
        }

        //forget sign out
        if(v.sign == 0 && checkIn != 0) {
            checkIn = v.time.tm_hour*60 + v.time.tm_min;
            signForgetDays++;
            continue;
        }

        //calculate
        if(v.sign == 0) {
            checkIn = v.time.tm_hour*60 + v.time.tm_min;
        }else if ( v.time.tm_hour*60 + v.time.tm_min - checkIn > 480) {
            overloadingDays++;
            checkIn = 0;
        }else {
            checkIn = 0;
        }

    }

    if(checkIn != 0) signForgetDays++;
    cout << checkId << "," << overloadingDays << "," << signForgetDays << endl;
    
}