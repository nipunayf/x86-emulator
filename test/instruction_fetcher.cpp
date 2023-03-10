#include "instruction_fetcher.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

TEST(ScannerTest, BasicScanning) {
  RegisterBank reg_bank;
  Memory memory;
  uint32_t last_eip = store_program(
    TEST_PATH + "instruction_fetcher/simple_input.txt", reg_bank, memory);
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32, last_eip);
  uint8_t expected_arr[4] = {0x8d, 0x4c, 0x24, 0};

  uint8_t byte;
  for (uint8_t i : expected_arr) {
    byte = ins_fetcher.next_byte();
    ASSERT_EQ(byte, i);
  }
}
