cmake_minimum_required(VERSION 3.6)
project(lamport_clock)

set(CMAKE_CXX_STANDARD 14)

include(include/lamport_clock.h)

add_library(lamport_clock INTERFACE)
add_subdirectory(tests)