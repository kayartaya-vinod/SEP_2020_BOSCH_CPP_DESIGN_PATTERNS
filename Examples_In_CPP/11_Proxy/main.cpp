#include <iostream>
#include <stdio.h>
#include <sstream>

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

// interface for the target and proxy

struct ProductDao {
    virtual void add(Product* p) = 0;
    virtual void update(Product* p) = 0;
    virtual void remove(int id) = 0;
    virtual void get(int id) = 0;
    static ProductDao* getInstance();
};

// the 'Target' implementation class
class ProductDaoImpl : public ProductDao
{
    ProductDaoImpl()
    {
    }

public:
    friend struct ProductDao;
    virtual void add(Product* p) override
    {
        cout << "ProductDao.add --> Adding a new product to DB - " << p->toStr() << endl;
    }
    virtual void update(Product* p) override
    {
        cout << "ProductDao.update --> Updating existing product in DB - " << p->toStr() << endl;
    }
    virtual void remove(int id) override
    {
        cout << "ProductDao.remove --> Deleting product with id - " << id << endl;
    }
    virtual void get(int id) override
    {
        cout << "ProductDao.get --> Getting product with id - " << id << endl;
    }
};

// proxy class -> has the exact same functionalities as the target; hence must implement the ProductDao interface
class ProductDaoTransactionProxy : public ProductDao
{
    // Proxy object maintains a reference/pointer to the actual target object
    ProductDao* target;

public:
    ProductDaoTransactionProxy(ProductDao* target)
        : target(target)
    {
    }
    virtual void add(Product* p)
    {
        // if(user.role not in ('admin', 'superuser'){
        //    throw runtime_erro('invalid access');
        // }
        // this method simply has to delegate the request to the actual target method;
        // but before that it can check for access, or do something else.
        cout << "PROXY: Beginning a new transaction" << endl;
        target->add(p);
        cout << "PROXY: committing the transaction after adding a new product" << endl;
    }
    virtual void update(Product* p) 
    {
        target->update(p);
    }
    virtual void remove(int id) 
    {
        target->remove(id);
    }
    virtual void get(int id) 
    {
        target->get(id);
    }
};

ProductDao* ProductDao::getInstance()
{
    return new ProductDaoTransactionProxy(new ProductDaoImpl);
}

int main()
{
    CLRSCR;

    cout << "Design patterns Demo - Proxy" << endl;
    LINE;

    // pointer of base class type can only point to
    // an object of the same class or objects of derived classes.

    //    ProductDao* dao = new ProductDaoTransactionProxy(new ProductDaoImpl);
    ProductDao* dao = ProductDao::getInstance(); // factory method approach for obtaining a proxy or real object
    // ProductDao* dao = new ProductDaoImpl;
    dao->add(new Product(1, "Apple Macbook Pro", 12500));
    dao->update(new Product(22, "Logitech Optical Mouse", 899));
    dao->get(1);
    dao->remove(22);
    dao->add(new Product(2, "Apple Macbook Air", 99000));
    dao->add(new Product(3, "Apple iPad", 45000));
}
