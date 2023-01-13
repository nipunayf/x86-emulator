#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define JMP_TEST_PATH (TEST_PATH + "jmp/")

#define JUMP(file_name, snapshot_size)                                         \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  store_program(JMP_TEST_PATH + file_name, reg_bank, memory);                  \
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);                \
  State state{ins_fetcher, reg_bank, memory};                                  \
                                                                               \
  uint32_t prev_value = reg_bank.load32(EAX);                                  \
  parse(state);                                                                \
                                                                               \
  ASSERT_EQ(state.snapshots.size(), snapshot_size);                            \
  ASSERT_EQ(reg_bank.load32(EAX), prev_value + 3);

// inc eax
// jmp 0x3
// inc eax
// inc eax
// inc eax
// inc eax
// inc eax
TEST(JmpTest, JmpEB){JUMP("jmpEB.txt", 4)}

// inc eax
// jmp 0x3
// inc eax
// inc eax
// inc eax
// inc eax
// inc eax
TEST(JmpTest, JmpE9){JUMP("jmpE9.txt", 4)}

// inc eax
// jb 0x3
// inc eax
// stc
// jb 0x3
// inc eax
// inc eax
// inc eax
// inc eax
TEST(JmpTest, Jmp72) {
  JUMP("jmp72.txt", 6)
}
