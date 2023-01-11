#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define PUSH_TEST_PATH (TEST_PATH + "push/")

#define PUSH(file_name, expected)                                              \
  {                                                                            \
    Scanner scanner(PUSH_TEST_PATH + file_name);                               \
    RegisterBank reg_bank;                                                     \
    Memory memory;                                                             \
    State state{scanner, reg_bank, memory};                                    \
    uint32_t initial_esp = reg_bank.load32(ESP);                               \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(memory.load32(initial_esp), expected);                           \
    ASSERT_EQ(reg_bank.load32(ESP), initial_esp - 4);                          \
  }

TEST(OpcodeTest, Push50){PUSH("push50.txt", reg_bank.load32(EAX))}

TEST(OpcodeTest, Push53){PUSH("push53.txt", reg_bank.load32(EBX))}

TEST(OpcodeTest, Push6A){PUSH("push6A.txt", 0x12)}

TEST(OpcodeTest, Push68){PUSH("push68.txt", 0x78563412)}

TEST(OpcodeTest, Push16) {
  PUSH("push16.txt", reg_bank.load_seg(SS))
}

// Enable the test when two byte opcodes are supported
// TEST(OpcodeTest, Push0FA8){PUSH("push0FA8.txt", reg_bank.load_seg(GS))}
