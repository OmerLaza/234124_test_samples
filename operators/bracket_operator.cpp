#include <exception>
#include <iostream>

using std::cout;
using std::endl;

class DivideBy
{
private:
    int divisor;

public:
    DivideBy(int d) : divisor(d)
    {
        if (d == 0)
        {
            throw ZeroDivisorException(); // IMPORTANT: if memory was allocated with new, you would need to delete it here
        }
    }

    int operator()(int dividend) const
    {
        return dividend / divisor;
    }

    // assignment operator
    DivideBy &operator=(const DivideBy &rhs)
    {
        divisor = rhs.divisor;
        return *this;
    }
    // copy constructor
    DivideBy(const DivideBy &rhs) : divisor(rhs.divisor) {}
    // destructor
    ~DivideBy() = default;

    class ZeroDivisorException : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Divisor cannot be zero";
        }
        ZeroDivisorException() = default;
    };
};

int main()
{
    DivideBy d(3);
    cout << d(3) << endl;
    cout << d(30) << endl;
    cout << d(10) << endl;
    d = DivideBy(0); // this will throw an exception
    return 0;
} // Notice this program will crash because of the ZeroDivisorException, which is thrown in the DivideBy constructor.
  // ***NOT MEMORY SAFE!***

/*
Output:
1
10
3
terminate called after throwing an instance of 'DivideBy::ZeroDivisorException'
  what():  Divisor cannot be zero
 */