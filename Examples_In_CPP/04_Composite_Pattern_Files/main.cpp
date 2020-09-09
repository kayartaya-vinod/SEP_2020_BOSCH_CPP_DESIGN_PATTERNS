#include <iostream>
#include <vector>

using namespace std;

// helper function for generating spaces

string spaces(int n)
{
    string s = "";
    for(int i = 0; i < n; i++) {
        s += " ";
    }
    return s;
}

// interface IFile -> instance of this represents either a file or a directory
struct IFile {
    virtual void print(int indent = 0) = 0;
};

// class File -> represents only a file object
class File : public IFile
{
    string name;

public:
    File(string name)
        : name(name)
    {
    }
    virtual void print(int indent = 0)
    {
        cout << spaces(indent) << "File: " << name << endl;
    }
};

// composite, as it is composed of files and sub directories
class Directory : public IFile
{
    string name;
    // composition
    vector<IFile*> content; // 0 or more IFile elements (files or directories)

public:
    Directory(string name)
        : name(name)
    {
    }

public:
    void add(IFile& fd)
    {
        content.push_back(&fd);
    }

    void print(int indent = 0)
    {
        cout << spaces(indent) << "Directory: " << name << endl;
        for(auto f : content) {
            f->print(indent + 4);
        }
    }
};

int main()
{

    File f1("Names.txt");
    File f2("picture.png");
    File f3("movie.mp4");

    Directory d1("root");
    d1.add(f1);
    d1.add(f2);
    d1.add(f3);

    Directory d1a("sub_dir1");
    File f4("course-intro.mp4");
    File f5("software-setup.mp4");
    File f6("section-overview.mp4");

    d1a.add(f4);
    d1a.add(f5);

    d1.add(d1a);
    d1a.add(f6);

    d1.print();

    return 0;
}