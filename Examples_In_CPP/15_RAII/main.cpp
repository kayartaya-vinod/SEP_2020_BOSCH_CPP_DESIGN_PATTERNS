#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <memory>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

mutex mut1;

class Resource
{
public:
    Resource()
    {
        cout << "A new resource is created!" << endl;
    }
    ~Resource()
    {
        cout << "The resource is getting destroyed!" << endl;
    }
    void hello()
    {
        cout << "Hello, world!" << endl;
    }
};

// custom scoep guard (need not be created, there are many apis exist)
class Guard{
    mutex *mut;
public:
    Guard(mutex *mut): mut(mut){
        mut->lock();
    }
    ~Guard(){
        mut->unlock();
    }
};

void print(string tname)
{
    mut1.lock();
    cout << "Printing from " << tname << " thread!" << endl;
    mut1.unlock(); // chances of this statement not reaching is high; and this causes dead lock
}

void guarded_print(string tname){
    Guard g1(&mut1);
    cout << "Printing from " << tname << " thread!" << endl;
    if(1) return;
}

void lock_guarded_print(string tname){
    lock_guard<mutex> g(mut1);
    cout << "Printing from " << tname << " thread!" << endl;
    if(1) return;
}

int main()
{
    CLRSCR;

    cout << "Design patterns Demo - RAII" << endl;
    LINE;
    
    {
        // some scope
        Resource *r1 = new Resource; 
        r1->hello();
        // resource leak
    }
    LINE;
    {
        unique_ptr<Resource> r1(new Resource); // RAII as well as Proxy pattern
        r1->hello();
    }
    LINE;
    {
        // only in C++ 14 onwards
        unique_ptr<Resource> r1 = make_unique<Resource>();
        r1->hello();
    }
    LINE;
    thread t1(lock_guarded_print, "t1");
    thread t2(lock_guarded_print, "t2");
    thread t3(lock_guarded_print, "t3");

    // execution of this halts until all the threads finish their task.
    t1.join();
    t2.join();
    t3.join();
}
