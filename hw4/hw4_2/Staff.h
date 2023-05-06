#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <cstdlib>
#include <string.h>
#include "Time.h"
using namespace std;

class Staff {
    public:
        //signIn = 0, singnOut = 1; time 小時轉分鐘
        string strTime;
        int employeeId, sign;
        Time time;
        Staff(int employeeId, int sign, string strTime){
            this->employeeId = employeeId;
            this->sign = sign;
            char timeYear[5], timeMonth[3], timeDay[3], timeHour[3], timeMin[3];
            this->strTime = strTime;
            memcpy(timeYear, strTime.c_str(), 4);
            memcpy(timeMonth, strTime.c_str()+4, 2);
            //cout << "***" << timeMonth<< endl;
            memcpy(timeDay, strTime.c_str()+6, 2);
            memcpy(timeHour, strTime.c_str()+8, 2);
            memcpy(timeMin, strTime.c_str()+10, 2);
            this->time = Time(atoi(timeYear), atoi(timeMonth), atoi(timeDay), atoi(timeHour)*60 + atoi(timeMin));
        }  
        Staff() {}
};
#endif