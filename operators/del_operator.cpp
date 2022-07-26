class A
{
private:
    int* a;
    int size;

public:
    explicit A(int size = 10) : a(new int[size]), size(size)
    {
        for (int i = 0; i < size; i++) {
            a[i] = i;
        }
    }

    ~A()
    {
        delete[] a;
    }

    A(const A& other) // copy C'tor
    {
        size = other.size;
        a = new int[other.getSize()];
        for (int i = 0; i < other.getSize(); i++) {
            a[i] = other.a[i];
        }
    }

    A& operator=(const A& other) // assignment operator
    {
        if (this != &other) {
            int new_size = other.getSize();
            int* new_data = new int[new_size];
            for (int i = 0; i < new_size; i++) {
                new_data[i] = other.a[i];
            }
            delete[] a;
            size = new_size; //equivalent to // this->size = new_size;
            a = new_data; // equivalent to // this->a = new_data;
        }
        return *this;
    }

    int getSize() const
    {
        return size;
    }

};

int main()
{
    A* arr = new A[10];
    A* a1 = new A(arr[5]);
    delete[] arr; // delete array
    delete a1; // delete object

    // this is memory safe, since we use delete[] which calls the destructor of A, as long as the destructor
    // deletes the memory allocated for each instance of A.
    return 0;
}
// memory safe :)
// no output