#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define XCHG_TEST_PATH (TEST_PATH + "xchg/")

#define XCHG(file_name, dest1, expected1, dest2, expected2)                    \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  store_program(XCHG_TEST_PATH + file_name, reg_bank, memory);                 \
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);                \
  State state{ins_fetcher, reg_bank, memory};                                  \
  parse(state);                                                                \
  RegisterBank original_reg_bank;                                              \
                                                                               \
  ASSERT_EQ(dest1, expected1);                                                 \
  ASSERT_EQ(dest2, expected2);                                                 \
  ASSERT_EQ(state.snapshots.size(), 1);

// xchg [edi + 0x11010110], dl
TEST(XchgTest, Xchg86){XCHG("xchg86.txt", reg_bank.load8(DL), 0,
                            memory.load8(reg_bank.load32(EDI) + 0x11010110),
                            original_reg_bank.load8(DL))}

// xchg esi, eax
TEST(XchgTest, Xchg87){XCHG("xchg87.txt", reg_bank.load32(EAX),
                            original_reg_bank.load32(ESI), reg_bank.load32(ESI),
                            original_reg_bank.load32(EAX))}

// xchg eax, edx
TEST(XchgTest, Xchg92) {
  XCHG("xchg92.txt", reg_bank.load32(EAX), original_reg_bank.load32(EDX),
       reg_bank.load32(EDX), original_reg_bank.load32(EAX))
}
