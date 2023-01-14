#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define DEC_TEST_PATH (TEST_PATH + "dec/")

#define DECREMENT(file_name, dest, expected)                                   \
  {                                                                            \
    INIT_STATE(DEC_TEST_PATH + file_name)                                      \
    RegisterBank original_reg_bank = reg_bank;                                 \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(dest, expected);                                                 \
    ASSERT_EQ(state.snapshots.size(), 1);                                      \
  }

TEST(DecTest, Dec40x) {
  INIT_STATE(DEC_TEST_PATH + "dec48.txt")
  RegisterBank original_reg_bank = reg_bank;
  parse(state);

  ASSERT_EQ(reg_bank.load32(EAX), original_reg_bank.load32(EAX) - 1);
  ASSERT_EQ(reg_bank.load32(EDX), original_reg_bank.load32(EDX) - 3);
  ASSERT_EQ(reg_bank.load32(EBP), original_reg_bank.load32(EBP) - 2);
  ASSERT_EQ(reg_bank.load32(ECX), original_reg_bank.load32(ECX) - 1);
  ASSERT_EQ(reg_bank.load32(EBX), original_reg_bank.load32(EBX) - 1);
  ASSERT_EQ(reg_bank.load32(EDI), original_reg_bank.load32(EDI) - 1);
  ASSERT_EQ(reg_bank.load32(ESI), original_reg_bank.load32(ESI) - 1);
  ASSERT_EQ(reg_bank.load32(ESP), original_reg_bank.load32(ESP) - 1);

  ASSERT_EQ(state.snapshots.size(), 11);
}

// dec al
TEST(DecTest, DecFE){
  DECREMENT("decFE.txt", reg_bank.load8(AL), original_reg_bank.load8(AL) - 1)}

// dec ebx
TEST(DecTest, DecFF) {
  DECREMENT("decFF.txt", reg_bank.load8(EBX), original_reg_bank.load8(EBX) - 1)
}
