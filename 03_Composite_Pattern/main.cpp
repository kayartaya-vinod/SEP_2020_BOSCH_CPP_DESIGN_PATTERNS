#include <iostream>
#include <stdio.h>
#include <vector>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;
// helper function to return a bunch of spaces:

string spaces(int count) {
    string s{};
    for(int i=0;i<count; i++){
        s+= " ";
    }
    return s;
}

// interface <Component>
struct HtmlElement{
    virtual string toString(int indent=3){
        return "";
    }
};

class Title : public HtmlElement
{
    string text{};

public:
    Title(string text)
        : text(text)
    {
    }
    virtual string toString(int indent=3)
    {
        return spaces(indent) +  "<title>" + text + "</title>";
    }
};


class Meta : public HtmlElement
{
    string name, content;

public:
    Meta(string name, string content)
        : name(name)
        , content(content)
    {
    }
    virtual string toString(int indent=3)
    {
        return spaces(indent) + "<meta name=\"" + name + "\" content=\"" + content + "\">";
    }
};


class H1 : public HtmlElement
{
    string text = "";

public:
    H1(string text)
        : text(text)
    {
    }
    virtual string toString(int indent=3)
    {
        return spaces(indent) + "<h1>" + text + "</h1>";
    }
};
	

class P : public HtmlElement
{
    string text = "";

public:
    P(string text)
        : text(text)
    {
    }

    virtual string toString(int indent=3)
    {
        return spaces(indent) + "<p>" + text + "</p>";
    }
};

class Container: public HtmlElement{
protected:
    vector<HtmlElement*> children;
public:
    void add(HtmlElement*elem){
        children.push_back(elem);
    }
    virtual string toString(int indent=3) {
        string str{};
        
        for(auto&el: children) {
            str += "\n" + el->toString(indent+3);
        }
        
        return str;
    }
};

class Div : public Container
{
public:
    virtual string toString(int indent=3)
    {
        return spaces(indent) + "<div>" + Container::toString(indent+3) + "\n" + spaces(indent) + "</div>";
    }
};


class Head : public Container
{
public:
    virtual string toString(int indent=3)
    {
        return spaces(indent) + "<head>" + Container::toString(indent+3) + "\n"+ spaces(indent) +  "</head>";
    }
};


class Body : public Container
{
public:
    virtual string toString(int indent=3)
    {
        return spaces(indent) + "<body>\n" + Container::toString(indent+3) + "\n" + spaces(indent) +  "</body>";
    }
};


class Html : public HtmlElement
{
    Head* head;
    Body* body;

public:
    void setHead(Head* head)
    {
        this->head = head;
    }
    void setBody(Body* body)
    {
        this->body = body;
    }
    virtual string toString(int indent=3)
    {
        return "<html>\n" + head->toString()  +"\n" + body->toString() + "\n</html>";
    }
};

int main()
{
    CLRSCR
    
	cout << "Design patterns Demo - COMPOSITE" << endl;
    LINE
    
    Head *head = new Head;
    head->add(new Meta("viewport", "width=device-width, initial-scale=1.0"));
    head->add(new Title("This is my awesome page"));
    
    Body *body =  new Body;
    body->add(new H1("Vinod Kumar Kayartaya"));
    
    // composites
    Div *div = new Div; // Level-2 Composite
    div->add(new P("Today is 2nd day of training"));
    div->add(new P("This is an example of Composite pattern"));
    
    Div *d2 = new Div; // Level-3 composite
    d2->add(new P("This is child element inside div tag"));
    div->add(d2);
    
    body->add(div); // Level-1 composite
    
    
    Div *d3 = new Div; // Level-4 composite
    d3->add(new P("This is level 4 composite"));
    d2->add(d3);
    
    
    Html*html = new Html;
    
    html->setHead(head);
    html->setBody(body);
    
    cout << html->toString() << endl;
    
    delete head;
    delete body;
    delete div;
    delete d2;
}
