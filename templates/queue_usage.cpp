#include <iostream>
#include "my_queue.h"
#include <vector>
#include <memory>

using namespace std;

class IntegerVector
{
public:
    vector<int> m_vector;

    IntegerVector() : m_vector()
    {
    }

    ~IntegerVector() = default; // default destructor is fine since we use unique_ptr

    IntegerVector(const IntegerVector& other) = delete; // copy constructor

    IntegerVector& operator=(const IntegerVector& other) = delete; // no assignment operator

    void push_back(int value)
    {
        m_vector.push_back(value);
    }
};

int main()
{
    Queue<int> number_queue;
    number_queue.pushBack(11);
    number_queue.pushBack(22);
    number_queue.pushBack(33);
    for (int i: number_queue) {
        cout << i << endl;
    }

    Queue<IntegerVector*> vector_queue;
    IntegerVector v1;
    v1.push_back(555);
    vector_queue.pushBack(&v1);
    IntegerVector v2;
    v2.push_back(555);
    v2.push_back(666);
    vector_queue.pushBack(&v2);
    for (IntegerVector* i: vector_queue) {
        for (int j: i->m_vector) {
            cout << j << ", ";
        }
        cout << endl;
    }

    return 0;
} // this is memory safe! all good :)

/*
Output:
 11
 22
 33
 555,
 555, 666,
 */