#include <iostream>
#include <stdio.h>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;


// Product-1 interface (in Diagram - Connection)
struct Printer {
    virtual void print() = 0;
    virtual ~Printer()
    {
    }
};
// Product-2 interface (in Diagram - Statement)
struct Scanner {
    virtual void scan() = 0;
    virtual ~Scanner()
    {
    }
};

// concrete implementations of product 1 (in Diagram Connection) - EpsonPrinter (in Diagram MySqlConnection), CanonPrinter (in Diagram OracleConnection)
class EpsonPrinter : public Printer
{
public:
    virtual void print() override
    {
        cout << "Printing using Epson printer" << endl;
    }
};
class CanonPrinter : public Printer
{
public:
    virtual void print() override
    {
        cout << "Printing using Canon printer" << endl;
    }
};

// concrete implementations of product 2 (Statemet) - EpsonScanner (MysqlStatement), CanonScanner (OracleStatement)
class EpsonScanner : public Scanner
{
public:
    virtual void scan() override
    {
        cout << "Scanning using Epson scanner" << endl;
    }
};
class CanonScanner : public Scanner
{
public:
    virtual void scan() override
    {
        cout << "Scanning using Canon scanner" << endl;
    }
};
	
    

// Abstract factory - factory of factories

class PrinterScannerFactory
{
public:
    virtual ~PrinterScannerFactory()
    {
    }
    
    // factory of factories
    virtual Printer* getPrinter() = 0;
    virtual Scanner* getScanner() = 0;
    
    // factory method to return an instance of a subtype of this class/
    // The paramter to this function is a discriminator, which generally is read/supplied via
    // environment variables or properties file or xml files (so, there is no need of parameter)
    static PrinterScannerFactory* getFactoryInstance(string printer_scanner_type);
};


// concrete factories (in diagram - MysqlFactory)
class EpsonFactory : public PrinterScannerFactory
{
public:
    virtual Printer* getPrinter() override
    {
        return new EpsonPrinter;
    }
    virtual Scanner* getScanner() override
    {
        return new EpsonScanner;
    }
};


//  (in diagram - OracleFactory)
class CanonFactory : public PrinterScannerFactory
{
public:
    virtual Printer* getPrinter() override
    {
        return new CanonPrinter;
    }
    virtual Scanner* getScanner() override
    {
        return new CanonScanner;
    }
};

// static function to get an instance of AnstractFactory
// The paramter to this function is a discriminator, which generally is read/supplied via
// environment variables or properties file or xml files (so, there is no need of parameter)
    
PrinterScannerFactory* PrinterScannerFactory::getFactoryInstance(string printer_scanner_type)
{
    if(printer_scanner_type.empty()) {
        printer_scanner_type = "Canon";
    }

    if(printer_scanner_type == "Epson") {
        cout << "returning a new EpsonFactory" << endl;
        return new EpsonFactory;
    }
    if(printer_scanner_type == "Canon") {
        cout << "returning a new CanonFactory" << endl;
        return new CanonFactory;
    }
    throw runtime_error("Invalid value for printer_scanner_type: " + printer_scanner_type);
}

int main()
{
    CLRSCR
    
	cout << "Design patterns Demo - Abstract factory" << endl;
    LINE
    
    PrinterScannerFactory* factory = PrinterScannerFactory::getFactoryInstance("Epson");

    Printer* printer = factory->getPrinter();
    printer->print();

    Scanner* scanner = factory->getScanner();
    scanner->scan();

    delete factory;
    delete printer;
    delete scanner;
}
