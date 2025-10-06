cmake_minimum_required(VERSION 3.11)

project(cpphello VERSION 0.1 DESCRIPTION "hello world")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(cpphello cpphello.cpp)
add_library(helloprint SHARED helloprint.cpp helloprint.h)
target_link_libraries(cpphello helloprint)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test PRIVATE
  GTest::gtest_main
  helloprint
)

include(GoogleTest)
gtest_discover_tests(hello_test)
