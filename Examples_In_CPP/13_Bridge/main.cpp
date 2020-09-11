#include <iostream>
#include <stdio.h>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

// interface for IMPLEMENTER (of the features)
// For example, A Television IMPLEMENTS the feature of SwitchOn/SwitchOFF, while it is triggered via a TvRemote
struct Device {
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
};

// concrete IMPLEMENTERS
class Television : public Device
{
public:
    virtual void on()
    {
        cout << "Television switched ON" << endl;
    }
    virtual void off()
    {
        cout << "Television switched OFF" << endl;
    }
    virtual void up()
    {
        cout << "Television volume UP" << endl;
    }
    virtual void down()
    {
        cout << "Television volume DOWN" << endl;
    }
};

class AirConditioner : public Device
{
public:
    virtual void on()
    {
        cout << "AirConditioner switched ON" << endl;
    }
    virtual void off()
    {
        cout << "AirConditioner switched OFF" << endl;
    }
    virtual void up()
    {
        cout << "AirConditioner temparature UP" << endl;
    }
    virtual void down()
    {
        cout << "AirConditioner temparature DOWN" << endl;
    }
};

// interface for ABSTRACTION (Features in the IMPLEMENTERS, but will be operated on the actual IMPLEMENTER itself)
struct RemoteControl {
    virtual void swtichOn() = 0;
    virtual void switchOff() = 0;
    virtual void increase() = 0;
    virtual void decrease() = 0;
};

// concrete classes of ABSTRACTION; must have a reference to an IMPLEMENTER
class TvRemote : public RemoteControl
{
    Television* tv;

public:
    TvRemote(Television* tv)
        : tv(tv)
    {
    }
    virtual void swtichOn()
    {
        tv->on();
    }
    virtual void switchOff()
    {
        tv->off();
    }
    virtual void increase()
    {
        tv->up();
    }
    virtual void decrease()
    {
        tv->down();
    }
};
class AcRemote : public RemoteControl
{
    AirConditioner* ac;

public:
    AcRemote(AirConditioner* ac)
        : ac(ac)
    {
    }
    virtual void swtichOn()
    {
        ac->on();
    }
    virtual void switchOff()
    {
        ac->off();
    }
    virtual void increase()
    {
        ac->up();
    }
    virtual void decrease()
    {
        ac->down();
    }
};
int main()
{
    CLRSCR;

    cout << "Design patterns Demo - Bridge" << endl;
    LINE;

    Television tv1;
    AirConditioner ac1;

    RemoteControl* rc;

    rc = new TvRemote(&tv1);
    rc->swtichOn();
    rc->increase();
    rc->decrease();
    rc->switchOff();
    
    rc = new AcRemote(&ac1);
    rc->swtichOn();
    rc->increase();
    rc->decrease();
    rc->switchOff();
    
    
}
