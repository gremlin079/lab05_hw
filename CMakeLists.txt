cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(banking_tests
    tests/AccountTest.cpp
    tests/TransactionTest.cpp
)
target_link_libraries(banking_tests
    PRIVATE
    banking
    GTest::GTest
    GTest::Main
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()

find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
if (LCOV_PATH AND GENHTML_PATH)
    add_custom_target(coverage
        COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info
        COMMAND ${LCOV_PATH} --remove coverage.info '*/tests/*' '/usr/*' --output-file coverage.info
        COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
