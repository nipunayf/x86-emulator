#include "register_bank.hpp"
#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>
#include <list>

#define REGISTER_BANK_TEST_PATH (TEST_PATH + "register_bank/")

TEST(RegisterBankTest, FlagTest) {
  RegisterBank reg_bank;
  std::list<std::string> flag_changes;

  ASSERT_EQ(reg_bank.load_flag(CF), 0);
  ASSERT_EQ(reg_bank.load_flag(AF), 0);
  reg_bank.set_flag(flag_changes, AF, 1);
  ASSERT_EQ(reg_bank.load_flag(AF), 1);
  ASSERT_EQ(reg_bank.load_flag(CF), 0);
}

TEST(RegisterBankTest, AddFlags) {
  Scanner scanner(REGISTER_BANK_TEST_PATH + "add_flags.txt");
  RegisterBank reg_bank;
  Memory memory;
  State state{scanner, reg_bank, memory};

  parse(state);

  // Result is 01111111 11111111 11111111 11111111
  ASSERT_EQ(reg_bank.load_flag(PF), 1);
  ASSERT_EQ(reg_bank.load_flag(SF), 0);
  ASSERT_EQ(reg_bank.load_flag(ZF), 0);
  ASSERT_EQ(reg_bank.load_flag(OF), 1);
  ASSERT_EQ(reg_bank.load_flag(AF), 0);
  ASSERT_EQ(reg_bank.load_flag(CF), 1);
}
