#include <iostream>
#include <stdio.h>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

// Excersise - create an HTML builder for generating an HTML content using builder pattern
/*
 * Head head;
 * head.add(new Title("this is title"))
 * .add(new Meta("x", "y"))
 * .add(new Meta("a", "b"));
 * 
 * Body body;
 * body.add(new Heading1("This is h1"));
 * 
 * Html html;
 * html.add(head)
 * .add(body);
 * 
 * html.build();
 * 
 * <html>
 * <head>
 * <title>this is title</title>
 * <meta name="x" content="y">
 * <meta name="a" content="b">
 * </head>
 * <body>
 * <h1>this is h1</h1>
 * </body>
 * <html>
 *  
 * 
*/

// SQL commands:
// 1. SELECT * FROM EMPLOYEES WHERE SALARY>=1200 AND DEPT='ADMIN' 
//    AND JOB_TITLE='MANAGER' OR JOB_TITLE='SALESMAN' ORDER BY SALARY desc, NAME asc
using namespace std;

class SqlBuilder
{
    string sql;
    bool table_specified = false;
    bool condition_specified = false;
    // provide a flag for "ORDER_BY" clause, with ascending/descending specification
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
