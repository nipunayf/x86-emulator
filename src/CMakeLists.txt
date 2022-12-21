cmake_minimum_required(VERSION 3.22)
project("emulator")

# Create the source library
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src "*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src "*.hpp")
add_library(emulator ${SOURCES} ${HEADERS})
