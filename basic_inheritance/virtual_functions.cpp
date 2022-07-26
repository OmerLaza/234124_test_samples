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

    virtual ~Shape()
    {
        cout << "Shape destructor" << endl;
    }

    virtual ostream& print(ostream& os) const // can also be pure virtual if you want to make it abstract
    {
        os << "Shape print" << endl;
        return os;
    }

    virtual double getArea() const = 0; // pure virtual function

    virtual Shape* clone() const = 0; // clone function, must be implemented in derived classes

    friend ostream& operator<<(ostream& os, const Shape& s);
};

ostream& operator<<(ostream& os, const Shape& s)
{
    return s.print(os);
}

class Circle : public Shape
{
private:
    double radius;

public:
    explicit Circle(double r) : radius(r),
                       Shape() // initializer list (here, Shape is called implicitly and not needed, but it's good practice to do it)
    {
        cout << "Circle constructor" << endl;
    }

    ~Circle() override
    {
        cout << "Circle destructor" << endl;
    }

    ostream& print(ostream& os) const override
    {
        os << "Circle print radius: " << radius;
        return os;
    }

    Circle* clone() const override
    {
        return new Circle(*this); // uses copy constructor
    }

    Circle(const Circle& other) : radius(other.radius),
                                  Shape() // copy constructor, the default here is good, but this for demonstration purposes
    {
        cout << "Circle copy constructor" << endl;
    }

    Circle&
    operator=(const Circle& other) // assignment operator, the default here is good, but this for demonstration purposes
    {
        if (this != &other) {
            radius = other.radius;
        }
        return *this;
    }

    double getArea() const override
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

    ~Rectangle() override
    {
        cout << "Rectangle destructor" << endl;
    }

    ostream& print(ostream& os) const override
    {
        os << "Rectangle print width: " << width << " height: " << height;
        return os;
    }

    Rectangle* clone() const override
    {
        return new Rectangle(*this); // uses copy constructor
    }

    double getArea() const override
    {
        return width * height;
    }
};

int main()
{
    Circle* c_ptr = new Circle(5);
    Rectangle* r_ptr = new Rectangle(5, 10);
    Shape* shapes[2] = {c_ptr, r_ptr};
    for (const Shape* shape: shapes) {
        cout << *shape << endl;
        cout << "Area: " << shape->getArea() << endl;
    }
    Shape* shapes2[2] = {shapes[0]->clone(), shapes[1]->clone()}; // clone usage example

    // delete usage example, can't use delete[] since it's a pointer, so it will only delete the pointer
    // also the shapes & shapes1 are not dynamically allocated, so they may not be deleted
    delete shapes[0];
    delete shapes[1];
    delete shapes2[0];
    delete shapes2[1];
    return 0;
}
/*
Output:
 Shape constructor
Circle constructor
Shape constructor
Rectangle constructor
Circle print radius: 5
Area: 78.5
Rectangle print width: 5 height: 10
Area: 50
Shape constructor
Circle copy constructor
Circle destructor
Shape destructor
Rectangle destructor
Shape destructor
Circle destructor
Shape destructor
Rectangle destructor
Shape destructor
 */