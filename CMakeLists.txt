cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_STANDARD 17)

# Основная библиотека
add_library(banking
  banking/Account.cpp
  banking/Transaction.cpp
)

# Поиск GTest
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
  )
  FetchContent_MakeAvailable(googletest)
endif()

# Тесты
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
