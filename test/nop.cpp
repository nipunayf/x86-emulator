#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define NOP_TEST_PATH (TEST_PATH + "nop/")

#define NOP_CHECK(file_name)                                                   \
  {                                                                            \
    RegisterBank reg_bank;                                                     \
    Memory memory;                                                             \
    store_program(NOP_TEST_PATH + file_name, reg_bank, memory);                \
    InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);              \
    State state{ins_fetcher, reg_bank, memory};                                \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(state.snapshots.size(), 1);                                      \
  }

// nop
TEST(NopTest, Nop90){NOP_CHECK("nop90.txt")}

// nop dword ptr [eax + eax]
TEST(NopTest, Nop0F1F) {
  NOP_CHECK("nop0F1F.txt")
}
