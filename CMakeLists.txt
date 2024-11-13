cmake_minimum_required(VERSION 3.30)

project(task2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(SOURCE_EXE main.cpp
        test.h)

add_executable(n1 ${SOURCE_EXE})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
        tests
        sharedPTR.h
        gtests.cpp
)

target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

enable_testing()
