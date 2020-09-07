#include <iostream>
#include <stdio.h>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

// SQL commands:
// 1. SELECT * FROM EMPLOYEES WHERE SALARY>=1200 AND DEPT='ADMIN' AND JOB_TITLE='MANAGER' OR JOB_TITLE='SALESMAN'
using namespace std;

class SqlBuilder
{
    string sql;
    bool table_specified = false;
    bool condition_specified = false;

public:
    SqlBuilder()
    {
    }
    ~SqlBuilder()
    {
    }

    // all the 'STEP' functions return a reference to the invoking object
    SqlBuilder& from(string table)
    {
        table_specified = true;
        sql = "SELECT * FROM " + table;
        return *this;
    }

    SqlBuilder& where(string condition)
    {
        if(!condition_specified) {
            sql += "\n\twhere " + condition;
            condition_specified = true;
        } else {
            sql += "\n\tand " + condition;
        }

        return *this;
    }

    SqlBuilder& where_or(string condition)
    {
        if(!condition_specified) {
            sql += "\n\twhere " + condition;
            condition_specified = true;
        } else {
            sql += "\n\tor " + condition;
        }

        return *this;
    }

    string build()
    {
        if(!table_specified)
            throw runtime_error("Table not specified");
        return this->sql;
    }
};

int main()
{
    CLRSCR

    cout << "Design patterns Demo - Builder" << endl;
    SqlBuilder sb;
    string sql = sb.from("employee")
                     .where("salary>=1200")
                     .where("dept='ADMIN'")
                     .where("job_title='MANAGER'")
                     .where_or("job_title='SALESMAN'")
                     .build();

    cout << "Generated sql is : " << sql << endl;

    LINE
}
