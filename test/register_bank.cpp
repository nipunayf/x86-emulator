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
  RegisterBank reg_bank;
  Memory memory;
  store_program(REGISTER_BANK_TEST_PATH + "add_flags.txt", reg_bank, memory);
  Scanner scanner(reg_bank, memory, OPERAND_32);
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
  Scanner scanner(reg_bank, memory, OPERAND_32);

  store_program(REGISTER_BANK_TEST_PATH + "nop.txt", reg_bank, memory);
  uint32_t prev_eip = reg_bank.load_eip();
  State state{scanner, reg_bank, memory};
  parse(state);
  ASSERT_EQ(reg_bank.load_eip(), prev_eip + 10);
  auto snapshot1 = state.snapshots.begin();
  ASSERT_STREQ(snapshot1->eip_transition.c_str(),
               "%eip(0x8048354) -> (0x804835d)");

  store_program(REGISTER_BANK_TEST_PATH + "add_flags.txt", reg_bank, memory);
  prev_eip = reg_bank.load_eip();
  parse(state);
  ASSERT_EQ(reg_bank.load_eip(), prev_eip + 6);
  auto snapshot2 = state.snapshots.begin();
  ASSERT_STREQ(snapshot2->eip_transition.c_str(),
               "%eip(0x8048354) -> (0x804835d)");
}
