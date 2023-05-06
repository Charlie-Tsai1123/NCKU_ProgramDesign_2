#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <cstdlib>
#include <ctime>
#include <string.h>
using namespace std;

class Staff {
    public:
        //signIn = 0, singnOut = 1; time 小時轉分鐘
        string strTime;
        struct tm time = {0};
        int employeeId, sign;
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
            this->time.tm_year = atoi(timeYear) - 1900;
            this->time.tm_mon = atoi(timeMonth) - 1;
            this->time.tm_mday = atoi(timeDay);
            this->time.tm_hour = atoi(timeHour);
            this->time.tm_min = atoi(timeMin);
        }
        Staff(){
            
        }
};
#endif