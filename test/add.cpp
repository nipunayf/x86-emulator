#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define REGISTER_BANK_TEST_PATH (TEST_PATH + "add/")

#define ADDITION(file_name, dest, expected)                                    \
  {                                                                            \
    Scanner scanner(REGISTER_BANK_TEST_PATH + file_name);                      \
    RegisterBank reg_bank;                                                     \
    Memory memory;                                                             \
    State state{scanner, reg_bank, memory};                                    \
    memory.store(0x00010200, 0x01a11001);                                      \
                                                                               \
    RegisterBank original_reg_bank = reg_bank;                                 \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(dest, expected);                                                 \
    ASSERT_EQ(state.snapshots.size(), 1);                                      \
  }

TEST(OpcodeTest, Add03){ADDITION("add03.txt", reg_bank.load32(EAX),
                                 original_reg_bank.load32(EAX) + 0x01a11001)}

TEST(OpcodeTest, Add05){ADDITION("add05.txt", reg_bank.load32(EAX),
                                 original_reg_bank.load32(EAX) + 0x10050301)}

TEST(OpcodeTest, Add80) {
  ADDITION("add80.txt", reg_bank.load8(AL), original_reg_bank.load8(AL) + 0x01)
}
