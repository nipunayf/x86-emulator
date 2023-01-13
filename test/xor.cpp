#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define XOR_TEST_PATH (TEST_PATH + "xor/")

#define XOR(file_name, dest, expected)                                         \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  store_program(XOR_TEST_PATH + file_name, reg_bank, memory);                  \
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);                \
  State state{ins_fetcher, reg_bank, memory};                                  \
  RegisterBank org_reg_bank;                                                   \
  parse(state);                                                                \
                                                                               \
  ASSERT_EQ(dest, expected);

TEST(XorTest, Xor33){XOR("xor33.txt", reg_bank.load32(EAX),
                         org_reg_bank.load32(EAX) ^ org_reg_bank.load32(EDX))}

TEST(XorTest, Xor35){
  XOR("xor35.txt", reg_bank.load32(EAX), org_reg_bank.load32(EAX) ^ 0x19004612)}

TEST(XorTest, Xor80) {
  XOR("xor80.txt", reg_bank.load8(AL), org_reg_bank.load8(AL) | 0x11)
}
