#include <iostream>
#include <stdio.h>
#include <sstream>
#include <sqlite3.h>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

// forward declaration
class EmployeeDao;
class CustomerDao;

class Customer {
    int id;
    string name;
public:
    Customer(int id, string name):
    id(id), name(name){}
    friend class CustomerDao;
};

/*
 * create table employees(id integer primary key, name varchar(50) not null, salary double);
 * create table customers(id integer primary key, name varchar(50) not null);
*/

class Employee {
    int id;
    string name;
    float salary;
public:
    Employee(int id, string name, float salary):
    id(id), name(name), salary(salary){}

    // usual members like getters/setters etc
    
    // avoid this and use getters in EmployeeDao
    friend class EmployeeDao;
};

class BaseDao {
public:
    // steps in template methods:
    virtual string getInsertSql()=0;

    // template methods:
    void insert(){
        sqlite3*db;
        if(sqlite3_open("example.db", &db)==0) {
            // db is opened successfully
            string sql = getInsertSql(); // this defined in the derived class -> EmployeeDao, ProductDao, ...
            char*err=0;
            int status = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
            if(status==SQLITE_OK) {
                cout << "Record inserted successfully!" << endl;
            }
            else {
                cout << "We encountered a problem while adding record!" << endl
                    << err << endl;
            }
        }
        else {
            throw runtime_error("Unable to open example.db");
        }
        
    }
    void update(){}
    void remove(){}

};

class EmployeeDao: public BaseDao{
    Employee *emp;
public:
    
    virtual string getInsertSql(){
        stringstream st;
        st << "insert into employees values ("
            << emp->id << ", '" << emp->name << "', " << emp->salary << ")";
        return st.str();
    }
    void insert(Employee *emp){
        this->emp=emp;
        BaseDao::insert(); // call to base class function
    }
};

class CustomerDao: public BaseDao {
    Customer *cust;
public:
    virtual string getInsertSql(){
        stringstream st;
        st << "insert into customers values ("
            << cust->id << ", '" << cust->name << "')";
        return st.str();
    }
    void insert(Customer *cust){
        this->cust=cust;
        BaseDao::insert(); // call to base class function
    }
};

	
int main()
{
    CLRSCR
    
	cout << "Design patterns Demo - Template Method" << endl;
    LINE

    
    EmployeeDao * dao;
    dao = new EmployeeDao();
    dao->insert(new Employee(103, "James", 3300)); 
    dao->insert(new Employee(104, "Miller", 4500));
    
    CustomerDao cdao;
    cdao.insert(new Customer(1, "Vinod"));
    cdao.insert(new Customer(2, "Shyam"));
}
