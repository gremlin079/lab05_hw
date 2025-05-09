cmake_minimum_required(VERSION 3.14)
project(banking)

option(COVERAGE "Enable code coverage" OFF)

set(CMAKE_CXX_STANDARD 17)

add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Coverage build enabled")
    target_compile_options(banking PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(banking PRIVATE --coverage)
endif()

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

target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(banking_tests
    PRIVATE
    banking
    gtest
    gmock
    gtest_main
)

if(COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking_tests PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(banking_tests PRIVATE --coverage)
endif()

enable_testing()
add_test(NAME banking_tests COMMAND banking_tests)


