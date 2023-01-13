#include "scanner.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

TEST(ScannerTest, BasicScanning) {
  RegisterBank reg_bank;
  Memory memory;
  store_program(TEST_PATH + "scanner/simple_input.txt", reg_bank, memory);
  Scanner scanner(reg_bank, memory, OPERAND_32);
  uint8_t expected_arr[4] = {0x8d, 0x4c, 0x24, 0};

  uint8_t byte;
  for (uint8_t i : expected_arr) {
    byte = scanner.next_byte();
    ASSERT_EQ(byte, i);
  }
}
