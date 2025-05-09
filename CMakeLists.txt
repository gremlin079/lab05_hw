cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_STANDARD 17)

add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(banking_tests
    tests/AccountTest.cpp
    tests/TransactionTest.cpp
)

target_link_libraries(banking_tests
    PRIVATE
    banking
    gtest
    gtest_main
)
