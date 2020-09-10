#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>

#define CLRSCR system("clear");
#define LINE cout << "------------------------------------------------------------------" << endl;

using namespace std;

class Product
{
    int id;
    string name;
    double price;

public:
    Product(int id, string name, double price)
        : id(id)
        , name(name)
        , price(price)
    {
    }

    string toStr()
    {
        stringstream ss;
        ss << "Product (id=" << id << ", name='" << name << "', price=₹" << price << ")";
        return ss.str();
    }
};

// observer/subscriber/listeners
// struct ProductListener{
//    virtual void onAddProduct(Product *p)=0;
//    virtual void onUpdateProduct(Product *p)=0;
//    virtual void onDeleteProduct(int id)=0;
//    virtual void onGetProduct(int id)=0;
//};

// to facilitate Interface Segregation Principle, divide the above interface into multiple interfaces
struct AddProductListener {
    virtual void onAddProduct(Product* p) = 0;
};
struct DeleteProductListener {
    virtual void onDeleteProduct(int id) = 0;
};

// product persister (dummy)
class ProductDao
{
    // requirement of observer pattern

    vector<AddProductListener*> addListeners;
    vector<DeleteProductListener*> deleteListeners;

public:
    // requirement of observer pattern
    void registerAddProductListener(AddProductListener* listener)
    {
        addListeners.push_back(listener);
    }
    void notifyAddProductListeners(Product* p)
    {
        for(auto& l : addListeners) {
            l->onAddProduct(p);
        }
    }
    void registerDeleteProductListener(DeleteProductListener* listener)
    {
        deleteListeners.push_back(listener);
    }
    void notifyDeleteProductListeners(int id)
    {
        for(auto& l : deleteListeners) {
            l->onDeleteProduct(id);
        }
    }
    // main business logic functions; from the Observer pattern's point of view, these are called events
    void add(Product* p)
    {
        notifyAddProductListeners(p);
        cout << "ProductDao.add --> Adding a new product to DB - " << p->toStr() << endl;
    }
    void update(Product* p)
    {
        cout << "ProductDao.update --> Updating existing product in DB - " << p->toStr() << endl;
    }
    void remove(int id)
    {
        notifyDeleteProductListeners(id);
        cout << "ProductDao.remove --> Deleting product with id - " << id << endl;
    }
    void get(int id)
    {
        cout << "ProductDao.get --> Getting product with id - " << id << endl;
    }
};

// concrete subscribers
class Logger : public AddProductListener
{
public:
    virtual void onAddProduct(Product* p)
    {
        // acutal implementation of Loggers may log into STDOUT/FILE/DB etc.
        cout << "INFO: a new product is being added - " << p->toStr() << endl;
    }
};

class EmailSender : public AddProductListener, public DeleteProductListener
{
public:
    virtual void onAddProduct(Product* p)
    {
        cout << "MAILER: Sending an email about a new product - " << p->toStr() << endl;
    }
    virtual void onDeleteProduct(int id)
    {
        cout << "MAILER: Sending an email about deleting of a product - " << id << endl;
    }
};

int main()
{
    CLRSCR;

    cout << "Design patterns Demo - Observer (publish/subscribe)" << endl;
    LINE;

    ProductDao dao;

    dao.registerAddProductListener(new Logger);
    dao.registerAddProductListener(new EmailSender);
    dao.registerDeleteProductListener(new EmailSender);

    dao.add(new Product(1, "Apple Macbook Pro", 12500));
    dao.update(new Product(22, "Logitech Optical Mouse", 899));
    dao.get(1);
    dao.remove(22);
    dao.add(new Product(2, "Apple Macbook Air", 99000));
    dao.add(new Product(3, "Apple iPad", 45000));
}
