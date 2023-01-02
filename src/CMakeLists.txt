cmake_minimum_required(VERSION 3.22)
project("emulator")

# Create the source library
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src "*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src "*.hpp")
list(REMOVE_ITEM SOURCES main.cpp)
add_library(emulator_lib ${SOURCES} ${HEADERS})

# Create main executable
add_executable(emulator main.cpp)
target_link_libraries(emulator emulator_lib)
