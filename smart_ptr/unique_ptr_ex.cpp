#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Car
{
private:
    std::string make;
    std::string model;
    int year;
    int price;

public:
    Car(std::string make, std::string model, int year, int price) : make(make), model(model), year(year), price(price)
    {
    }

    ~Car() = default;

    Car(const Car& other) = default;

    Car& operator=(const Car& other) = default;

    std::string getName() const
    {
        return make + " " + model;
    }
};

class CarDealership
{
private:
    std::string owner;
    string name;
    int cash;
    std::vector<std::unique_ptr<Car>> cars;

public:
    CarDealership(std::string owner, string name, int cash) : owner(owner), name(name), cash(cash)
    {
    }

    ~CarDealership() = default;                                    // default destructor is fine since we use unique_ptr
    CarDealership(const CarDealership& other) = delete;            // copy constructor
    CarDealership& operator=(const CarDealership& other) = delete; // no assignment operator
    void addCar(std::unique_ptr<Car> car)
    {
        cars.push_back(std::move(car));
    }

    void printCars() const
    {
        for (const std::unique_ptr<Car>& car: cars) {
            std::cout << car->getName() << std::endl;
        }
    }
};

int main()
{
    CarDealership dealership("John", "Best Dealership", 1000000);
    std::unique_ptr<Car> car1(new Car("Ford", "Focus", 2015, 20000));
    std::unique_ptr<Car> car2(new Car("Ford", "Mustang", 2016, 30000));
    std::unique_ptr<Car> car3(new Car("Ford", "Fusion", 2017, 40000));
    dealership.addCar(std::move(car1));
    dealership.addCar(std::move(car2));
    dealership.addCar(std::move(car3));
    dealership.printCars();
    return 0;
}
// **NOTICE**
// no memory leak here, since we use unique_ptr to manage memory, the destructor of CarDealership will be called automatically
// it holds vector of unique_ptr, so the destructor of vector will call the destructor of unique_ptr,
// which will call the destructor of Car

/*
Output:
 Ford Focus
 Ford Mustang
 Ford Fusion
 */
