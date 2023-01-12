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

TEST(RegisterBankTest, InstructionPointer) {
  RegisterBank reg_bank;
  Memory memory;

  uint32_t prev_eip = reg_bank.load_eip();
  Scanner scanner1(REGISTER_BANK_TEST_PATH + "nop.txt");
  State state1{scanner1, reg_bank, memory};
  parse(state1);
  ASSERT_EQ(reg_bank.load_eip(), prev_eip + 0x90);
  auto snapshot1 = state1.snapshots.begin();
  ASSERT_STREQ(snapshot1->eip_transition.c_str(),
               "%eip(0x8048354) -> (0x80483e4)");

  prev_eip = reg_bank.load_eip();
  Scanner scanner2(REGISTER_BANK_TEST_PATH + "add_flags.txt");
  State state2{scanner2, reg_bank, memory};
  parse(state2);
  ASSERT_EQ(reg_bank.load_eip(), prev_eip + 0x50);
  auto snapshot2 = state2.snapshots.begin();
  ASSERT_STREQ(snapshot2->eip_transition.c_str(),
               "%eip(0x80483e4) -> (0x8048434)");
}
