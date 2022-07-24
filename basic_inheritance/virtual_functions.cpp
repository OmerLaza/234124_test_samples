#include <iostream>
#include <string>
#define PI 3.14

using namespace std;

class Shape
{
public:
    Shape()
    {
        cout << "Shape constructor" << endl;
    }
    ~Shape()
    {
        cout << "Shape destructor" << endl;
    }
    virtual ostream &print(ostream &os) const // can also be pure virtual if you want to make it abstract
    {
        os << "Shape print" << endl;
        return os;
    }

    virtual int getArea() const = 0; // pure virtual function

    friend ostream &operator<<(ostream &os, const Shape &s);
};

ostream &operator<<(ostream &os, const Shape &s)
{
    return s.print(os);
}

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r) : radius(r), Shape() // initializer list (here, Shape is called implicitly and not needed, but it's good practice to do it)
    {
        cout << "Circle constructor" << endl;
    }
    ~Circle()
    {
        cout << "Circle destructor" << endl;
    }
    ostream &print(ostream &os) const override
    {
        os << "Circle print radius: " << radius << endl;
        return os;
    }
    int getArea() const override
    {
        return radius * radius * PI; // PI is a constant defined above
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h), Shape()
    {
        cout << "Rectangle constructor" << endl;
    }
    ~Rectangle()
    {
        cout << "Rectangle destructor" << endl;
    }
    ostream &print(ostream &os) const override
    {
        os << "Rectangle print width: " << width << " height: " << height << endl;
        return os;
    }
    int getArea() const override
    {
        return width * height;
    }
};

int main()
{
    Circle c(5);
    Rectangle r(5, 10);
    Shape *shapes[2] = {&c, &r};
    for (int i = 0; i < 2; i++)
    {
        cout << *shapes[i] << endl;
        cout << "Area: " << shapes[i]->getArea() << endl;
    }
    return 0;
}
