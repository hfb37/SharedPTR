#include "sharedPTR.h"
#include <gtest/gtest.h>
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
    explicit MyStruct(int v) : value(v) {}
};


TEST(tests, intTEST) {
    auto ptr = make_shared<int>(10);
    EXPECT_EQ(10, *ptr.get());
    EXPECT_EQ(1, ptr.use_count());
    auto ptr2(ptr);
    EXPECT_EQ(10, *ptr2.get());
    EXPECT_EQ(2, ptr2.use_count());
    ptr.release();
    EXPECT_EQ(1, ptr2.use_count());
}

TEST(tests, stdVectorTest) {
    auto ptr = make_shared<std::vector<int>>(10, 10);
    EXPECT_EQ(ptr.get()->size(), 10);
    EXPECT_EQ((*ptr.get())[0], 10);
    ptr.get()->push_back(20);
    EXPECT_EQ(ptr.get()->size(), 11);
    EXPECT_EQ((*ptr.get())[10], 20);
    auto ptr2 = make_shared<std::vector<int>>(2);
    ptr.swap(ptr2);
    EXPECT_EQ(ptr.get()->size(), 2);
}

TEST(tests, MyStructTest) {
    auto ptr1MS = make_shared<MyStruct>(10);
    auto ptr2MS = make_shared<MyStruct>(5);
    auto ptr3MS(ptr1MS);
    EXPECT_EQ(ptr1MS.use_count(), 2);
    EXPECT_EQ(ptr2MS.use_count(), 1);
    EXPECT_EQ(ptr3MS->value, 10);
    EXPECT_EQ(ptr2MS->value, 5);
    ptr3MS.release();
    ptr3MS = ptr2MS;
    EXPECT_EQ(ptr1MS.use_count(), 1);
    EXPECT_EQ(ptr2MS.use_count(), 2);
    EXPECT_EQ(ptr3MS->value, 5);
}

TEST(tests, arrayTest) {
    auto arrptr2 = make_shared<int[3], array_deleter<int>>(10, 20, 30);
    EXPECT_EQ(*arrptr2.get(), 10);
    EXPECT_EQ(*(arrptr2.get() + 1), 20);
}

TEST(tests, resetTest){
    auto ptr = make_shared<int>(10);
    EXPECT_EQ(*ptr.get(), 10);
    ptr = new int(20);
    EXPECT_EQ(*ptr.get(), 20);
    ptr.reset(new int(30));
    EXPECT_EQ(*ptr.get(), 30);
}