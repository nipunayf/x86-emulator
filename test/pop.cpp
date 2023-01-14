#include "opcode.hpp"
#include "operand.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define POP_TEST_PATH (TEST_PATH + "pop/")

#define POP(file_name, expected, increment)                                    \
  {                                                                            \
    INIT_STATE(POP_TEST_PATH + file_name)                                      \
    uint32_t initial_esp = reg_bank.load32(ESP);                               \
    uint32_t initial_mem = memory.load(ESP, increment);                        \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(expected, initial_mem);                                          \
    ASSERT_EQ(reg_bank.load32(ESP), initial_esp + (1 << increment));           \
  }

TEST(PopTest, Pop58){POP("pop58.txt", reg_bank.load32(EAX), OPERAND_32)}

TEST(PopTest, Pop53){POP("pop5A.txt", reg_bank.load32(EDX), OPERAND_32)}

TEST(PopTest, Pop1F){POP("pop1F.txt", reg_bank.load_seg(DS), OPERAND_16)}

TEST(PopTest, Pop8F) {
  POP("pop8F.txt", reg_bank.load32(EAX), OPERAND_32)
}

// Enable the test when two byte opcodes are supported
// TEST(PopTest, Pop0FA9){POP("pop0FA9.txt", reg_bank.load_seg(GS),
// OPERAND_16)}
