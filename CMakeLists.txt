cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

set(CMAKE_CXX_STANDARD 17)

add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(banking PRIVATE --coverage)
endif()

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

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking_tests PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(banking_tests PRIVATE --coverage)
endif()

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
enable_testing()
add_test(NAME banking_tests COMMAND banking_tests)
