#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define AND_TEST_PATH (TEST_PATH + "and/")

#define AND(file_name, dest, expected)                                         \
  INIT_STATE(AND_TEST_PATH + file_name)                                        \
  RegisterBank org_reg_bank;                                                   \
  parse(state);                                                                \
                                                                               \
  ASSERT_EQ(dest, expected);

TEST(AndTest, And50){AND("and21.txt", reg_bank.load32(EDX),
                         org_reg_bank.load32(EDX) & org_reg_bank.load32(EAX))}

TEST(AndTest, And53){
  AND("and25.txt", reg_bank.load32(EAX), org_reg_bank.load32(EAX) & 0x19004612)}

TEST(AndTest, And83) {
  AND("and83.txt", reg_bank.load32(EAX), org_reg_bank.load32(EAX) & 0x11)
}
