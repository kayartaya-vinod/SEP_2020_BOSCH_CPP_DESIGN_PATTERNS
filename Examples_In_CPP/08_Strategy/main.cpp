#include <iostream>
#include <stdio.h>
#include <string.h>


#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

class ArrayUtil;
class EmployeeIdComparable;
class EmployeeSalaryComparable;
class EmployeeNameComparable;

class Employee
{
    int id;
    string name;
    double salary;

public:
    Employee(int id, string name, double salary)
        : id(id)
        , name(name)
        , salary(salary)
    {
    }
    friend class ArrayUtil;
    friend void print(Employee* emps, int size);
    friend class EmployeeIdComparable;
    friend class EmployeeSalaryComparable;
    friend class EmployeeNameComparable;
};


// interface strategy 
struct EmployeeComparable{
    virtual int compare(Employee c1, Employee c2)=0; // 0-> e1==e2, -ve -> e1<e2 +ve -> e1>e2
};

class ArrayUtil
{
    // strategy
    EmployeeComparable *ec;
public:
    void setEmployeeComparable(EmployeeComparable *ec){
        this->ec = ec;
    }
    
    void sort(Employee* emps, int size, EmployeeComparable *ec){
        this->setEmployeeComparable(ec);
        this->sort(emps, size);
    }
    
    void sort(Employee* emps, int size)
    {
        for(int i = 0; i < size - 1; i++) {
            for(int j = i + 1; j < size; j++) {
                if( ec->compare(emps[i], emps[j]) >0  ) { // strategy, based on which the actual sorting takes place.
                    // swap
                    Employee temp = emps[i];
                    emps[i] = emps[j];
                    emps[j] = temp;
                }
            }
        }
    }
};

// concrete strategy implementations
class EmployeeIdComparable: public EmployeeComparable {
public:
    virtual int compare(Employee e1, Employee e2){
        return e1.id - e2.id;
    }
};
class EmployeeSalaryComparable: public EmployeeComparable {
public:
    virtual int compare(Employee e1, Employee e2){
        return (int)(e1.salary - e2.salary);
    }
};
class EmployeeNameComparable: public EmployeeComparable {
public:
    virtual int compare(Employee e1, Employee e2){
        return strcmp(e1.name.c_str(), e2.name.c_str());
    }
};

void print(Employee* emps, int size)
{
    for(int i = 0; i < size; i++) {
        cout << emps[i].id << ", " << emps[i].name << ", " << emps[i].salary << endl;
    }
    cout << endl;
}




int main()
{
    CLRSCR

    cout << "Design patterns Demo - Strategy" << endl;

    LINE Employee emps[] = { 
        Employee(101, "Scott", 2300), 
        Employee(12, "Martin", 1020), 
        Employee(34, "James", 1200),
        Employee(982, "Miller", 2200), 
        Employee(55, "Wills", 2400) 
        };
    int len = 5;

    print(emps, len);
    ArrayUtil au;
    // set the strategy for sorting
//    au.setEmployeeComparable(new EmployeeIdComparable);
//    au.sort(emps, len);
//    print(emps, len);
//    
//    au.setEmployeeComparable(new EmployeeSalaryComparable);
//    au.sort(emps, len);
//    print(emps, len);
//    
//    au.setEmployeeComparable(new EmployeeNameComparable);
//    au.sort(emps, len);
//    print(emps, len);

    au.sort(emps, len, new EmployeeIdComparable); // lambda/arrow functions
    print(emps, len);
    
    au.sort(emps, len, new EmployeeSalaryComparable);
    print(emps, len);
    
    au.sort(emps, len, new EmployeeNameComparable);
    print(emps, len);
}
