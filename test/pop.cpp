#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define POP_TEST_PATH (TEST_PATH + "pop/")

#define POP(file_name, expected, increment)                                    \
  {                                                                            \
    Scanner scanner(POP_TEST_PATH + file_name);                                \
    RegisterBank reg_bank;                                                     \
    Memory memory;                                                             \
    State state{scanner, reg_bank, memory};                                    \
    uint32_t initial_esp = reg_bank.load32(ESP);                               \
    uint32_t initial_mem = memory.read(ESP);                                   \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(expected, initial_mem);                                          \
    ASSERT_EQ(reg_bank.load32(ESP), initial_esp + increment);                  \
  }

TEST(OpcodeTest, Pop58){POP("pop58.txt", reg_bank.load32(EAX), 4)}

TEST(OpcodeTest, Pop53){POP("pop5A.txt", reg_bank.load32(EDX), 4)}

TEST(OpcodeTest, Pop1F){POP("pop1F.txt", reg_bank.load_seg(DS), 2)}

TEST(OpcodeTest, Pop8F) {
  POP("pop8F.txt", reg_bank.load32(EAX), 4)
}

// Enable the test when two byte opcodes are supported
// TEST(OpcodeTest, Pop0FA9){POP("pop0FA9.txt", reg_bank.load_seg(GS))}
