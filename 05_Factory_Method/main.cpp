#include <iostream>

using namespace std;

// interface Printer
struct Printer {
    virtual ~Printer()
    {
    }
    virtual void print() = 0;
    virtual void printInColor(bool isColor) = 0;
    virtual void setPaperType(string paperType) = 0;

    // factory method can be part of the abstract super/base type.

    // generally, the factory method is written by a different developer than the one who
    // created Printer and its subtyptes. So, we can keep this function as global function of some
    // header file/library and make use of it.
    static Printer* getPrinter(string printer);
};

// concrete implementations (printers installed on your PC)
class CanonPrinter : public Printer
{
    bool isColor;
    string paperType;

public:
    CanonPrinter(bool isColor = true, string paperType = "A4")
        : isColor(isColor)
        , paperType(paperType)
    {
    }
    virtual void printInColor(bool isColor)
    {
        this->isColor = isColor;
    }
    virtual void setPaperType(string paperType)
    {
        this->paperType = paperType;
    }
    virtual void print()
    {
        cout << "Printing using Canon Printer in " << (isColor ? "color " : "black/white ") << "on " << paperType
             << " paper." << endl;
    }
};

class EpsonPrinter : public Printer
{
    bool isColor;
    string paperType;

public:
    EpsonPrinter(bool isColor = true, string paperType = "A4")
        : isColor(isColor)
        , paperType(paperType)
    {
    }
    virtual void printInColor(bool isColor)
    {
        this->isColor = isColor;
    }
    virtual void setPaperType(string paperType)
    {
        this->paperType = paperType;
    }
    virtual void print()
    {
        cout << "Printing using Epson Printer in " << (isColor ? "color " : "black/white ") << "on " << paperType
             << " paper." << endl;
    }
};

class HpPrinter : public Printer
{
    bool isColor;
    string paperType;

public:
    HpPrinter(bool isColor = true, string paperType = "A4")
        : isColor(isColor)
        , paperType(paperType)
    {
    }
    virtual void printInColor(bool isColor)
    {
        this->isColor = isColor;
    }
    virtual void setPaperType(string paperType)
    {
        this->paperType = paperType;
    }
    virtual void print()
    {
        cout << "Printing using HP Printer in " << (isColor ? "color " : "black/white ") << "on " << paperType
             << " paper." << endl;
    }
};

// factory method in Printer class
Printer* Printer::getPrinter(string printer = "")
{
    if(printer == "HP") {
        return new HpPrinter;
    }
    if(printer == "EPSON") {
        return new EpsonPrinter;
    }
    if(printer == "CANON" || printer == "") {
        return new CanonPrinter;
    }

    throw runtime_error("Either the printer [" + printer + "] is not found or not connected");
}

// Factory of printers
// cannot inherit; cannot instantiate
class PrinterFactory final
{
    // to make a single instance available always (singleton)
    static Printer* thePrinter;

    PrinterFactory()
    {
    }

public:
    // factory methods usually take one or more parameters, called discriminators
    // using which objects of appropriate types are manufactured and returned
    static Printer* getPrinter(string printer = "")
    {
        if(thePrinter) {
            // already initialized
            return thePrinter;
        }

        if(printer == "HP") {
            thePrinter = new HpPrinter;
        }
        if(printer == "EPSON") {
            thePrinter = new EpsonPrinter;
        }
        if(printer == "CANON" || printer == "") {
            thePrinter = new CanonPrinter;
        }

        if(thePrinter) {
            // already initialized
            return thePrinter;
        }

        throw runtime_error("Either the printer [" + printer + "] is not found or not connected");
    }
};

Printer* PrinterFactory::thePrinter = 0;

void line()
{
    for(int i = 0; i < 80; i++)
        cout << "-";

    cout << endl;
}

int main()
{
    cout << "Design patterns - Factory method pattern Demo" << endl;
    line();

    cout << "Choose one of the printers listed below: " << endl;
    cout << "1. HP" << endl;
    cout << "2. Epson" << endl;
    cout << "3. Canon" << endl;
    cout << "4. Xerox" << endl;
    cout << "Enter your choice (1-4): ";
    int printerChoice;
    cin >> printerChoice;

    cout << "Do you want to print in color? (1 for true, 0 for false): ";
    bool isColor;
    cin >> isColor;

    cout << "Enter the paper type: (A4/A5/Letter/Legal/Statement/...) ";
    string paperType;
    cin >> paperType;

    Printer* printer;
    string printers[] = { "", "HP", "EPSON", "CANON", "Xerox" };

    try {
        //        printer = PrinterFactory::getPrinter(printers[printerChoice]);
        //        printer = PrinterFactory::getPrinter("HP"); // returns the priviously created printer object
        //        printer = PrinterFactory::getPrinter("Xerox"); // returns the priviously created printer object

        printer = Printer::getPrinter(printers[printerChoice]);

        // the application is using a printer with out knowing what kind of printer being used!!!
        printer->printInColor(isColor);
        printer->setPaperType(paperType);
        printer->print();
        delete printer;
        line();
    } catch(runtime_error ex) {
        cout << "Something went wrong!!" << endl;
        cout << ex.what() << endl;
    }
}
