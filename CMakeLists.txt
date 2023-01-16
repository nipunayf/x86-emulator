cmake_minimum_required(VERSION 3.22)
project(x86-emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS --coverage)

enable_testing()

add_definitions(-w)

# Add subdirectories
add_subdirectory("src")
add_subdirectory("test")
