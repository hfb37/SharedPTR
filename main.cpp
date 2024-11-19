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

int main() {
    SharedPTR<int> ptr;
    ptr = new int(50);
}