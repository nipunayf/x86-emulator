cmake_minimum_required(VERSION 3.22)
project("test")

# Fetch google test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Install test executables
file(GLOB TESTS *.cpp)
foreach (test ${TESTS})
    string(REPLACE "${CMAKE_SOURCE_DIR}/test/" "" temp ${test})
    string(REPLACE ".cpp" "" test_exe ${temp})
    add_executable(${test_exe} ${test})
    target_link_libraries(${test_exe} emulator GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${test_exe})
endforeach (test ${TESTS})

# Install test resources
file(COPY ${CMAKE_SOURCE_DIR}/test/res DESTINATION ${CMAKE_BINARY_DIR}/test)
