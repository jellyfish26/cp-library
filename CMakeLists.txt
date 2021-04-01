cmake_minimum_required(VERSION 3.10)
add_definitions("-Wall -Wextra -O2 -std=c++17")
project("cp-library")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(cp.out main.cc)
