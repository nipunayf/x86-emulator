#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define NOT_TEST_PATH (TEST_PATH + "not/")

#define NOT(file_name, dest, expected)                                         \
  Scanner scanner(NOT_TEST_PATH + file_name);                                  \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  State state{scanner, reg_bank, memory};                                      \
  parse(state);                                                                \
  RegisterBank org_reg_bank;                                                   \
                                                                               \
  ASSERT_EQ(dest, expected);

TEST(NotTest, Not50) {
  NOT("notF7.txt", reg_bank.load32(ECX), ~org_reg_bank.load32(ECX))
}
