#include "register_bank.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

TEST(RegisterBankTest, FlagTest) {
  RegisterBank reg_bank;

  ASSERT_EQ(reg_bank.load_flag(CF), 0);
  ASSERT_EQ(reg_bank.load_flag(AF), 0);
  reg_bank.set_flag(AF, 1);
  ASSERT_EQ(reg_bank.load_flag(AF), 1);
  ASSERT_EQ(reg_bank.load_flag(CF), 0);
}
