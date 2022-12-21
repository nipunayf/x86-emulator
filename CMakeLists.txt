cmake_minimum_required(VERSION 3.22)
project(x86-emulator)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# Add subdirectories
add_subdirectory("src")
add_subdirectory("test")
