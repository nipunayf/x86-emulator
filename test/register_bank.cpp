#include "register_bank.hpp"
#include "parse.hpp"
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
  INIT_STATE(REGISTER_BANK_TEST_PATH + "add_flags.txt")
  parse(state);

  // Result is 01111111 11111111 11111111 11111111
  ASSERT_EQ(reg_bank.load_flag(PF), 1);
  ASSERT_EQ(reg_bank.load_flag(SF), 0);
  ASSERT_EQ(reg_bank.load_flag(ZF), 0);
  ASSERT_EQ(reg_bank.load_flag(OF), 1);
  ASSERT_EQ(reg_bank.load_flag(AF), 0);
  ASSERT_EQ(reg_bank.load_flag(CF), 1);
}

TEST(RegisterBankTest, InstructionPointer) {
  INIT_STATE(REGISTER_BANK_TEST_PATH + "nop.txt")

  uint32_t prev_eip = reg_bank.load_eip();
  parse(state);
  ASSERT_EQ(reg_bank.load_eip(), prev_eip + 9);
  auto snapshot1 = state.snapshots.begin();
  ASSERT_STREQ(snapshot1->eip_transition.c_str(),
               "%eip(0x8048354) -> (0x804835d)");

  last_eip =
    store_program(REGISTER_BANK_TEST_PATH + "add_flags.txt", reg_bank, memory);
  ins_fetcher.set_last_eip(last_eip);
  prev_eip = reg_bank.load_eip();
  parse(state);
  ASSERT_EQ(reg_bank.load_eip(), prev_eip + 5);
  auto snapshot2 = state.snapshots.begin();
  ASSERT_STREQ(snapshot2->eip_transition.c_str(),
               "%eip(0x8048354) -> (0x804835d)");
}
