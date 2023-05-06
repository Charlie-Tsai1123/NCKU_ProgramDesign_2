#include "check.h"

void check (vector<Staff> staff) {
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