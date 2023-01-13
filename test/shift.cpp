#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define SHIFT_TEST_PATH (TEST_PATH + "shift/")

#define SHIFT(file_name, dest, expected, cf_flag)                              \
  Scanner scanner(SHIFT_TEST_PATH + file_name);                                \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  State state{scanner, reg_bank, memory};                                      \
  uint32_t initial_esp = reg_bank.load32(ESP);                                 \
  parse(state);                                                                \
                                                                               \
  ASSERT_EQ(dest, expected);                                                   \
  ASSERT_EQ(reg_bank.load_flag(CF), cf_flag);

TEST(ShiftTest, SARC1){SHIFT("sarC1.txt", reg_bank.load32(EAX), 0xefe36c51, 0)}

TEST(ShiftTest, SHLD3){
  SHIFT("shlD3.txt", memory.load32(reg_bank.load32(EBX) + 0x78562312), 0, 0)}

TEST(ShiftTest, SHRD1) {
  SHIFT("shrD1.txt", reg_bank.load32(EAX), 0x5fc6d8a2, 0)
}
