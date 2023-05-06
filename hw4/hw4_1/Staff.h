#ifndef STAFF_H
#define STAFF_H
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
#endif