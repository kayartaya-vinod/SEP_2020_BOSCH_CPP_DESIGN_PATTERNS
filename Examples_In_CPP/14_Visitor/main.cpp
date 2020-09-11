#include <iostream>
#include <stdio.h>
#include <sstream>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

// forward declarations
class Circle;
class Triangle;

// interface for VISITOR
struct Transformer {
    // visit functions
    virtual string transform(Circle* c) = 0;
    virtual string transform(Triangle* c) = 0;
};

// interface for ELEMENT
struct Shape {
    virtual string transform(Transformer* t) = 0;
};

// concrete ELEMENTS
class Circle : public Shape
{
    double radius;

public:
    Circle(double radius)
        : radius(radius)
    {
    }
    double getRadius()
    {
        return radius;
    }
    virtual string transform(Transformer* t) // t is a pointer to an XmlTransformer or JsonTransformer or etc.
    {
        // first dispatch
        return t->transform(this);
    }
    // additional functions like setters etc
};
class Triangle : public Shape
{
    double base, height;

public:
    Triangle(double base, double height)
        : base(base)
        , height(height)
    {
    }
    double getBase()
    {
        return base;
    }
    double getHeight()
    {
        return height;
    }
    virtual string transform(Transformer* t)
    {
        return t->transform(this);
    }
    // additional functions like setters etc
};

// concrete version of VISITOR
class XmlTransformer : public Transformer
{
public:
    virtual string transform(Circle* c)
    {
        stringstream ss;
        ss << "<?xml version=\"1.0\"?>" << endl
           << "<circle>" << endl
           << "\t<radius>" << c->getRadius() /* second dispatch*/ << "</radius>" << endl
           << "</circle>" << endl;

        return ss.str();
    }
    virtual string transform(Triangle* t)
    {
        stringstream ss;
        ss << "<?xml version=\"1.0\"?>" << endl
           << "<triangle>" << endl
           << "\t<base>" << t->getBase() /* second dispatch*/ << "</base>" << endl
           << "\t<height>" << t->getHeight() /* second dispatch*/ << "</height>" << endl
           << "</triangle>" << endl;

        return ss.str();
    }
};

class JsonTransformer : public Transformer
{

public:
    virtual string transform(Circle* c)
    {
        stringstream ss;
        ss << "{" << endl << "\t\"radius\": " << c->getRadius() /* second dispatch*/ << endl << "}" << endl;

        return ss.str();
    }
    virtual string transform(Triangle* t)
    {
        stringstream ss;
        ss << "{" << endl
           << "\t\"base\": " << t->getBase() /* second dispatch*/ << "," << endl
           << "\t\"height\": " << t->getHeight() /* second dispatch*/ << endl
           << "}" << endl;

        return ss.str();
    }
};

int main()
{
    CLRSCR;

    cout << "Design patterns Demo - Visitor" << endl;
    LINE;

    Circle c1(12.34);
    Triangle t1(12.34, 56.78);

    // call to get a specific representation of circle
    string xml;
    xml = c1.transform(new XmlTransformer);
    cout << "c1 in XML format is : " << endl << xml << endl;

    xml = t1.transform(new XmlTransformer);
    cout << "t1 in XML format is : " << endl << xml << endl;

    string json;
    json = c1.transform(new JsonTransformer);
    cout << "c1 in JSON format is : " << endl << json << endl;

    json = t1.transform(new JsonTransformer);
    cout << "t1 in JSON format is : " << endl << json << endl;
}
