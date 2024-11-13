#include "sharedPTR.h"
#include <iostream>
#include <vector>


template< typename T >
struct array_deleter
{
    void operator ()( T const * p)
    {
        delete[] p;
    }
};

struct MyStruct {
    int value;

    explicit MyStruct(int v) : value(v) {};
};

int main()
    {
    auto ptr = make_shared<int>(10);
    std::cout << *ptr.get() << ' ';
    ptr = new int(20);
    std::cout << *ptr.get() << ' ';

}