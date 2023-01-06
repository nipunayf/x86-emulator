#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define INC_TEST_PATH (TEST_PATH + "inc/")

TEST(OpcodeTest, Inc40x) {
  Scanner scanner(INC_TEST_PATH + "inc40.txt");
  RegisterBank reg_bank;
  Memory memory;
  State state{scanner, reg_bank, memory};

  RegisterBank original_reg_bank = reg_bank;
  parse(state);

  ASSERT_EQ(reg_bank.load32(EAX), original_reg_bank.load32(EAX) + 1);
  ASSERT_EQ(reg_bank.load32(EDX), original_reg_bank.load32(EDX) + 3);
  ASSERT_EQ(reg_bank.load32(EBP), original_reg_bank.load32(EBP) + 2);
  ASSERT_EQ(reg_bank.load32(ECX), original_reg_bank.load32(ECX) + 1);
  ASSERT_EQ(reg_bank.load32(EBX), original_reg_bank.load32(EBX) + 1);
  ASSERT_EQ(reg_bank.load32(EDI), original_reg_bank.load32(EDI) + 1);
  ASSERT_EQ(reg_bank.load32(ESI), original_reg_bank.load32(ESI) + 1);
  ASSERT_EQ(reg_bank.load32(ESP), original_reg_bank.load32(ESP) + 1);

  ASSERT_EQ(state.snapshots.size(), 11);
}
