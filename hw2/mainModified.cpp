#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

int cmp(const void* a, const void* b);
class Staff {
    private:
        int employee_id, age, gender, salary;
    
    public:
    void set_employee_id(int employee_id) {
        this->employee_id = employee_id;
    }

    void set_age(int age) {
        this->age = age;
    }

    void set_gender(int gender) {
        this->gender = gender;
    }

    void set_salary(int salary) {
        this->salary = salary;
    }

    int get_employee_id() {
        return this->employee_id;
    }

    int get_age() {
        return this->age;
    }

    int get_gender() {
        return this->gender;
    }

    int get_salary() {
        return this->salary;
    }
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
        staff[num].set_employee_id(stoi(str));
        getline(file, str, ',');
        staff[num].set_age(stoi(str));
        getline(file, str, ',');
        if(strcmp(str.c_str(), "f") == 0) staff[num].set_gender(0);
        else staff[num].set_gender(1);
        getline(file, str);
        staff[num].set_salary(stoi(str));
        num ++;
    }

    qsort(staff, num, sizeof(Staff), cmp);

    int tempSalary = staff[0].get_salary();
    cout << staff[0].get_salary();
    for(int i=0; i<num; i++) {
        if(tempSalary != staff[i].get_salary()) {
            tempSalary = staff[i].get_salary();
            cout << endl << staff[i].get_salary() << ",";
            cout << staff[i].get_employee_id();
        }else {
            cout << "," << staff[i].get_employee_id();
        }
    }
    cout << endl;  
    return 0;
}

int cmp(const void* a, const void* b) {
     Staff* x = (Staff*) a;
     Staff* y = (Staff*) b;

    if((*x).get_salary() != (*y).get_salary()) return (*x).get_salary() - (*y).get_salary();
    if((*x).get_age() != (*y).get_age()) return (*x).get_age() - (*y).get_age();
    if((*x).get_gender() != (*y).get_gender()) return (*x).get_gender() - (*y).get_gender();
    return (*x).get_employee_id() - (*y).get_employee_id();
}

