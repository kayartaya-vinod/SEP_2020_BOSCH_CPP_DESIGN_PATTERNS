#include <iostream>
#include <stdio.h>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

// interface Reader
struct Reader {
    virtual string source() = 0;
    virtual int read() = 0; // supposed to read one byte from the source at a time and return int version of the same
};

// concrete Readers
class FileReader : public Reader
{
public:
    virtual string source()
    {
        return "File";
    }
    virtual int read()
    {
        cout << "reading 1 byte from file" << endl;
        return 0; // not implementing the actual reading of bytes from files.
    }
};
class SocketReader : public Reader
{
public:
    virtual string source()
    {
        return "Socket";
    }
    virtual int read()
    {
        cout << "reading 1 byte from socket" << endl;
        return 0; // not implementing the actual reading of bytes from Socket.
    }
};
class KeyboardReader : public Reader
{
public:
    virtual string source()
    {
        return "Keyboard";
    }
    virtual int read()
    {
        cout << "reading 1 byte from Keyboard" << endl;
        return 0; // not implementing the actual reading of bytes from Keyboard.
    }
};

// Decorator for reading lines from different sources

class LineReader
{ // int the books, it says you have to inherit from Reader; let's not do it!!!
    Reader* reader;

public:
    LineReader(Reader* reader)
        : reader(reader)
    {
    }

    string readLine()
    {
        //        string str = "";
        //        while((int ch=reader->read())!='\n'){
        //            str += (char)ch;
        //        }
        //        return str;
        cout << "started reading a line from a " << reader->source() << endl;
        for(int i=0; i<5; i++){
            reader->read(); // dummy impl as of now.
        }
        cout << "finished reading a line from a " << reader->source() << endl << endl;
        return "";
    }
};

int main()
{
    CLRSCR

    cout << "Design patterns Demo - Decorator" << endl;
    LINE
    
    FileReader fr;
    SocketReader sr;
    KeyboardReader kr;
    
    LineReader *lr;
    
    lr = new LineReader(&fr);
    lr->readLine(); // acting on a file as a source
    
    lr = new LineReader(&sr);
    lr->readLine(); // acting on a socket as a source
    
    lr = new LineReader(&kr);
    lr->readLine(); // acting on a keybaord as a source
    
    
}
