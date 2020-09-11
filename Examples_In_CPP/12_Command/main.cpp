#include <iostream>
#include <stdio.h>
#include <vector>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

// abstract Receiver (for example, 'File' in the usecase of text editor)
struct Server {
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void start() = 0;
    virtual void shutdown() = 0;
    virtual void reboot() = 0;
    virtual void runDiagnostics() = 0;
};

class UsaServer : public Server
{
public:
    virtual void connect()
    {
        cout << "connected to UsaServer" << endl;
    }
    virtual void disconnect()
    {
        cout << "disconnected from UsaServer" << endl;
    }
    virtual void start()
    {
        cout << "Started UsaServer" << endl;
    }
    virtual void shutdown()
    {
        cout << "Shutdown UsaServer" << endl;
    }
    virtual void reboot()
    {
        cout << "Rebooted UsaServer" << endl;
    }
    virtual void runDiagnostics()
    {
        cout << "Running diagnostics on UsaServer" << endl;
    }
};

class AsiaServer : public Server
{
public:
    virtual void connect()
    {
        cout << "connected to AsiaServer" << endl;
    }
    virtual void disconnect()
    {
        cout << "disconnected from AsiaServer" << endl;
    }
    virtual void start()
    {
        cout << "Started AsiaServer" << endl;
    }
    virtual void shutdown()
    {
        cout << "Shutdown AsiaServer" << endl;
    }
    virtual void reboot()
    {
        cout << "Rebooted AsiaServer" << endl;
    }
    virtual void runDiagnostics()
    {
        cout << "Running diagnostics on AsiaServer" << endl;
    }
};

// interface for Abstract Command
struct Command {
    virtual void execute() = 0;
};

// concrete commands representing the indivual actions to be executed on receivers
class StartCommand : public Command
{
    Server* server;

public:
    StartCommand(Server* server)
        : server(server)
    {
    }
    virtual void execute()
    {
        server->start();
    }
};
class ShutdownCommand : public Command
{
    Server* server;

public:
    ShutdownCommand(Server* server)
        : server(server)
    {
    }
    virtual void execute()
    {
        server->shutdown();
    }
};
class RebootCommand : public Command
{
    Server* server;

public:
    RebootCommand(Server* server)
        : server(server)
    {
    }
    virtual void execute()
    {
        server->reboot();
    }
};
class ConnectCommand : public Command
{
    Server* server;

public:
    ConnectCommand(Server* server)
        : server(server)
    {
    }
    virtual void execute()
    {
        server->connect();
    }
};
class DisconnectCommand : public Command
{
    Server* server;

public:
    DisconnectCommand(Server* server)
        : server(server)
    {
    }
    virtual void execute()
    {
        server->disconnect();
    }
};
class RunDiagnosticsCommand : public Command
{
    Server* server;

public:
    RunDiagnosticsCommand(Server* server)
        : server(server)
    {
    }
    virtual void execute()
    {
        server->runDiagnostics();
    }
};

// invoker of comamnds ('Button' for example, in the text editor usecase)
class Invoker
{
    // one or more commands will be kept in the invoker
    // for example, in case of text editor, "Save" button will have only "saveCommand" object, which in turn
    // has a reference to the target of operation (receiver) which is nothing but the actual file that you are editing
    vector<Command*> commands;

public:
    void addCommand(Command* command)
    {
        commands.push_back(command);
    }
    // function to execute all commands (for example, when the 'Button', is clicked, execute the 'saveCommand')
    void executeJob()
    {
        for(auto& cmd : commands) {
            try{
                cmd->execute();
            }
            catch(exception ex){
                // handle exceptions; rollback transactions (undo using Memento pattern)
            }
        }
    }
};

int main()
{
    CLRSCR;

    cout << "Design patterns Demo - Command" << endl;
    LINE;

    // commands operate on these receivers:
    AsiaServer* asiaServer = new AsiaServer;
    UsaServer* usaServer = new UsaServer;
    
    // Creating an invoker to execute a job
    Invoker invoker;
    invoker.addCommand(new ConnectCommand(asiaServer));
    invoker.addCommand(new StartCommand(asiaServer));
    invoker.addCommand(new DisconnectCommand(asiaServer));
    invoker.addCommand(new ConnectCommand(usaServer));
    invoker.addCommand(new RunDiagnosticsCommand(usaServer));
    invoker.addCommand(new ShutdownCommand(usaServer));
    invoker.addCommand(new DisconnectCommand(usaServer));
    
    // execute the job
    invoker.executeJob();
}
