#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define JMP_TEST_PATH (TEST_PATH + "jmp/")

// inc eax
// jmp 0x3
// inc eax
// inc eax
// inc eax
// inc eax
// inc eax
TEST(JmpTest, JmpEB) {
  RegisterBank reg_bank;
  Memory memory;
  store_program(JMP_TEST_PATH + "jmpEB.txt", reg_bank, memory);
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);
  State state{ins_fetcher, reg_bank, memory};

  uint32_t prev_value = reg_bank.load32(EAX);
  parse(state);

  ASSERT_EQ(reg_bank.load32(EAX), prev_value + 3);
}
