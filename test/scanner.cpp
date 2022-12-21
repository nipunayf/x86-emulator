#include <gtest/gtest.h>
#include <filesystem>
#include "../src/scanner.hpp"

TEST(ScannerTest, BasicScanning) {
    Scanner scanner(std::filesystem::current_path().string() + "/res/scanner/simple_input.txt");
    uint8_t expected_arr[4] = {0x8d, 0x4c, 0x24, 0};

    uint16_t byte;
    for (uint16_t i: expected_arr) {
        byte = scanner.next();
        ASSERT_EQ(byte, i);
    }
}
