#include <iostream>

using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base constructor" << endl;
    }
    ~Base()
    {
        cout << "Base destructor" << endl;
    }
    virtual void print() 
    {
        cout << "Base print" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived constructor" << endl;
    }
    ~Derived()
    {
        cout << "Derived destructor" << endl;
    }
    void print() override
    {
        cout << "Derived print" << endl;
    }
};

int main()
{
    Derived d;
    d.print();
    return 0;
}

/* Output:
Base constructor
Derived constructor
Derived print
Derived destructor
Base destructor
*/
