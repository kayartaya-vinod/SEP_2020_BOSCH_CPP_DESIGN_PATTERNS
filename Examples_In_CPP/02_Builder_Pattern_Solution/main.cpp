#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define CLRSCR system("clear")
#define LINE cout << "------------------------------------------------------------------" << endl

// Excersise - create an HTML builder for generating an HTML content using builder pattern
/*
 * Head head;
 * head.add(new Title("this is title"))
 * .add(new Meta("x", "y"))
 * .add(new Meta("a", "b"));
 *
 * Body body;
 * body.add(new Heading1("This is h1"));
 * body.add(new Heading2("This is h2"));
 * body.add(new Heading3("This is h3"));
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

using namespace std;

// Abtract interface ---------------
class Content
{
public:
    virtual string GetContent() = 0;
};

class Header : public Content
{
    string stringHeader;

public:
    Header()
    {
        stringHeader = "<head>\n";
    };
    ~Header(){};
    Header& add(Content* ct)
    {
        stringHeader += ct->GetContent() + "\n";
        return *this;
    } // do i need any improvement regarding Context class and new line?
    string GetHeader()
    {
        return stringHeader;
    }
    string GetContent()
    {
        return (stringHeader + "</header>\n");
    }
};

class Title : public Content
{
    string text;

public:
    Title(string txt)
    {
        text = "<title>" + txt + "</title>";
    };
    ~Title(){};
    string GetContent()
    {
        return text;
    }
};

class Meta : public Content
{
    string mt;

public:
    Meta(string a, string b)
    {
        mt = "<meta name=\"" + a + "\" content=\"" + b + "\">";
    };
    ~Meta(){};
    string GetContent()
    {
        return mt;
    }
};

//////////////////////////////// end of HEADER
/* Class to build body */
class Body : public Content
{
    string bd;

public:
    Body()
    {
        bd = "<body>\n";
    };
    ~Body(){};
    Body& add(Content* ct)
    {
        bd += ct->GetContent() + "\n";
        return *this;
    };
    string GetBody()
    {
        return bd;
    };
    string GetContent()
    {
        return (bd + "</body>\n");
    } // how to handle enclosed html tag?
};

class Heading1 : public Content
{
    string heading1;

public:
    Heading1(string hd1)
    {
        heading1 += "<h1>" + hd1 + "</h1>";
    }
    ~Heading1(){};
    string GetContent()
    {
        return heading1;
    }
};

class Heading2 : public Content
{
    string heading2;

public:
    Heading2(string hd2)
    {
        heading2 += "<h2>" + hd2 + "</h2>";
    }
    ~Heading2(){};
    string GetContent()
    {
        return heading2;
    }
};
//////////////////////////////// end of BODY

class HtmlBuilder
{
    string html;

public:
    HtmlBuilder()
    {
        html = "<html>\n";
    };
    ~HtmlBuilder(){};
    HtmlBuilder& add(Content* ct)
    {
        html += ct->GetContent() + "\n";
        return *this;
    };
    void Build()
    {
        html += "</html>";
    }; // adding closing tag
    string GetFinalString()
    {
        return html;
    };
};

int main()
{
    CLRSCR;

    Header hd;
    hd.add(new Title("This is Title")).add(new Meta("x", "y"));

    Body body;
    body.add(new Heading1("This is Heading1 <h1> tag")).add(new Heading2("This is Heading2 <h2> tag"));

    HtmlBuilder htmltxt;
    htmltxt.add(&hd).add(&body).Build();

    LINE;
    cout << htmltxt.GetFinalString() << endl;
    LINE;
    return 0;
}