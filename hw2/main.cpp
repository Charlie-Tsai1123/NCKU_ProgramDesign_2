#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

int cmp(const void* a, const void* b);
class Staff {
    public:
        int employee_id, age, gender, salary;
};

int main(int argc, char** argv) {
    ifstream file(argv[1]);
    if(!file.is_open()) {
        cerr << "wrong" << endl;
        return 1;
    }

    Staff staff[10000];
    int num = 0;
    string str;
    while(getline(file, str, ',')) {
        staff[num].employee_id = stoi(str);
        getline(file, str, ',');
        staff[num].age = stoi(str);
        getline(file, str, ',');
        if(strcmp(str.c_str(), "f") == 0) staff[num].gender = 0;
        else staff[num].gender = 1;
        getline(file, str);
        staff[num].salary = stoi(str);
        num ++;
    }

    qsort(staff, num, sizeof(Staff), cmp);

    int tempSalary = staff[0].salary;
    cout << staff[0].salary;
    for(int i=0; i<num; i++) {
        if(tempSalary != staff[i].salary) {
            tempSalary = staff[i].salary;
            cout << endl << staff[i].salary << ",";
            cout << staff[i].employee_id;
        }else {
            cout << "," << staff[i].employee_id;
        }
    }
    cout << endl;  
    return 0;
}

int cmp(const void* a, const void* b) {
    const Staff* x = (Staff*) a;
    const Staff* y = (Staff*) b;

    if((*x).salary != (*y).salary) return (*x).salary - (*y).salary;
    if((*x).age != (*y).age) return (*x).age - (*y).age;
    return (*x).gender - (*y).gender;
}

