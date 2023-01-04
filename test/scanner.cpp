#include "scanner.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

TEST(ScannerTest, BasicScanning) {
  Scanner scanner(TEST_PATH + "scanner/simple_input.txt");
  uint8_t expected_arr[4] = {0x8d, 0x4c, 0x24, 0};

  uint8_t byte;
  for (uint8_t i : expected_arr) {
    byte = scanner.next_byte();
    ASSERT_EQ(byte, i);
  }
}
