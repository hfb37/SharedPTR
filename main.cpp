#include "sharedPTR.h"
#include <iostream>
#include <vector>

struct MyStruct {
    int value;

    explicit MyStruct(int v) : value(v) {
        std::cout << "Object with value " << value << " was created." << std::endl;
    }

    ~MyStruct() {
        std::cout << "Object with value " << value << " was destroyed." << std::endl;

    }
};

int main()
    {
    auto ptr1MS = make_shared<MyStruct>(10);
    auto ptr2MS = make_shared<MyStruct>(5);
    auto ptr3MS(ptr1MS);
    std::cout << "MyStruct1 use count is " << ptr1MS.use_count() << "\n";
    std::cout << "MyStruct2 use count is " << ptr2MS.use_count() << "\n";
    std::cout << "Value of MyStruct1 is " << ptr1MS->value << "\n";
    std::cout << "Value of MyStruct3 is " << ptr3MS->value << "\n";
    ptr3MS.release();
    ptr3MS = ptr2MS;
    std::cout << "MyStruct1 use count after release is " << ptr1MS.use_count() << "\n";
    std::cout << "MyStruct2 use count is " << ptr2MS.use_count() << "\n";
    std::cout << "Value of MyStruct3 is " << ptr3MS->value << "\n\n";

    auto ptrV = make_shared<std::vector<int>>(10);
    std::cout << "Vector V is ";
    for(auto it = ptrV->begin(); it != ptrV->end(); it++) {
        std::cout << *it << ' ';
    }
    std::cout << "\n";
}