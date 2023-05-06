#include "check.h"

bool cmpMax(tuple<int, int, char[9]>, tuple<int, int, char[9]>);
void check (vector<Staff> staff) {
    tuple<int, int, char[9]> maxIdDay[3]; //0:id 1:maxday
    get<0>(maxIdDay[0]) = 0;
    get<1>(maxIdDay[0]) = 0;
    get<0>(maxIdDay[1]) = 0;
    get<1>(maxIdDay[1]) = 0;
    get<0>(maxIdDay[2]) = 0;
    get<1>(maxIdDay[2]) = 0;
    tuple<int, int, char[9]> current;
    get<0>(current) = 0;
    get<1>(current) = 0;
    int currentYear = 0, currentMonth = 0, currentDay = 0, currentContinue = 0;
    for (auto &v: staff) {
        if(get<0>(current) != v.employeeId) {
            if(currentContinue > get<1>(current)) get<1>(current) = currentContinue;

            //current較大
            if(cmpMax(current, maxIdDay[2])) {
                get<0>(maxIdDay[2]) = get<0>(current);
                get<1>(maxIdDay[2]) = get<1>(current);
                sort(maxIdDay, maxIdDay + 3, cmpMax);
            }
            get<0>(current) = v.employeeId;
            get<1>(current) = 1;
            currentYear = v.timeYear;
            currentMonth = v.timeMonth;
            currentDay = v.timeDay;
            currentContinue = 1;
        }else if(currentYear == v.timeYear && currentMonth == v.timeMonth && currentDay == v.timeDay) {
            continue;
        }else if(currentYear == v.timeYear && currentMonth == v.timeMonth && currentDay == v.timeDay-1){
            currentContinue++;
        }else if(currentContinue > get<1>(current)) {
            get<1>(current) = currentContinue;
            currentContinue = 1;
            currentYear = v.timeYear;
            currentMonth = v.timeMonth;
            currentDay = v.timeDay;
        }else {
            currentContinue = 1;
            currentYear = v.timeYear;
            currentMonth = v.timeMonth;
            currentDay = v.timeDay;
        }
    }
}

bool cmpMax(tuple<int, int,char[9]> a, tuple<int, int, char[9]>b) {
    if(get<1>(a) == get<1>(b)) return get<0>(a) < get<0>(b);
    return get<1>(a) > get<1>(b);
}