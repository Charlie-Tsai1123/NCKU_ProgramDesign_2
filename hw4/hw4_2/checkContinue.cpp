#include "checkContinue.h"

bool checkContinue(pair<Staff, int> a, Staff b) {
    struct tm start = {0};
    struct tm end = {0};
    start.tm_year = a.first.time.year - 1900;
    start.tm_mon = a.first.time.month - 1;
    start.tm_mday = a.first.time.day;
    end.tm_year = b.time.year - 1900;
    end.tm_mon = b.time.month - 1;
    end.tm_mday = b.time.day;

    time_t startTime = mktime(&start);
    time_t endTime = mktime(&end);

    double diffTime = difftime(endTime, startTime);
    int diffDay = diffTime / (60*60*24);
    return diffDay == 1;
}