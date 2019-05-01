cmake_minimum_required(VERSION 3.9)
project(heap_lab_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(heap_lab_1 main.cpp)

add_subdirectory(gtests)

include_directories(gtests/googletest/include)
include_directories(gtests/googlemock/include)

target_link_libraries(heap_lab_1 gtest gtest_main)
