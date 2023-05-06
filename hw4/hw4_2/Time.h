#ifndef TIME_H
#define TIME_H

class Time {
    public:
        int year, month, day, time;
        Time(int year, int month, int day, int time) {
            this->year = year;
            this->month = month;
            this->day = day;
            this->time = time;
        }
        Time() {}
};

#endif