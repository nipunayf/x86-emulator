#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define OR_TEST_PATH (TEST_PATH + "or/")

#define OR(file_name, dest, expected)                                          \
  INIT_STATE(OR_TEST_PATH + file_name)                                         \
  parse(state);                                                                \
  RegisterBank org_reg_bank;                                                   \
                                                                               \
  ASSERT_EQ(dest, expected);

TEST(OrTest, Or0B){OR("or0B.txt", reg_bank.load32(EAX),
                      org_reg_bank.load32(EAX) | org_reg_bank.load32(EBX))}

TEST(OrTest, Or0D){
  OR("or0D.txt", reg_bank.load32(EAX), 0x12457656 | org_reg_bank.load32(EAX))}

TEST(OrTest, Or81) {
  OR("or81.txt", reg_bank.load32(EAX), org_reg_bank.load32(EAX) | 0x11111111)
}
