#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define NOT_TEST_PATH (TEST_PATH + "not/")

#define NOT(file_name, dest, expected)                                         \
  INIT_STATE(NOT_TEST_PATH + file_name)                                        \
  parse(state);                                                                \
  RegisterBank org_reg_bank;                                                   \
                                                                               \
  ASSERT_EQ(dest, expected);

TEST(NotTest, Not50) {
  NOT("notF7.txt", reg_bank.load32(ECX), ~org_reg_bank.load32(ECX))
}
