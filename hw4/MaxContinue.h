#ifndef MAXCONTINUE_H
#define MAXCONTINUE_H
#include <string>

class MaxContinue {
    public:
        int employeeId, continueDay;
        string initialTime, finalTime;
        MaxContinue(int employeeId, int continueDay, string initialTime, string finalTime) {
            this->employeeId = employeeId;
            this->continueDay = continueDay;
            this->initialTime = initialTime;
            this->finalTime = finalTime;
        }

        MaxContinue() {
            
        }
};

#endif