#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define ADD_TEST_PATH (TEST_PATH + "add/")

#define ADDITION(file_name, dest, expected)                                    \
  {                                                                            \
    RegisterBank reg_bank;                                                     \
    Memory memory;                                                             \
    store_program(ADD_TEST_PATH + file_name, reg_bank, memory);                \
    Scanner scanner(reg_bank, memory, OPERAND_32);                             \
    State state{scanner, reg_bank, memory};                                    \
    std::string memory_change;                                                 \
    memory.store32(memory_change, 0x00010200, 0x01a11001);                     \
                                                                               \
    RegisterBank original_reg_bank = reg_bank;                                 \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(dest, expected);                                                 \
    ASSERT_EQ(state.snapshots.size(), 1);                                      \
  }

// add bl, al
TEST(AddTest, Add00){ADDITION("add00.txt", (int8_t)reg_bank.load8(BL),
                              (int8_t)original_reg_bank.load8(AL) +
                                (int8_t)original_reg_bank.load8(BL))}

// add edi, ecx
TEST(AddTest, Add01){ADDITION("add01.txt", (int32_t)reg_bank.load32(ECX),
                              (int32_t)original_reg_bank.load32(EDI) +
                                (int32_t)original_reg_bank.load32(ECX))}

// add al, bl
TEST(AddTest, Add02){ADDITION("add02.txt", (int8_t)reg_bank.load8(AL),
                              (int8_t)original_reg_bank.load8(BL) +
                                (int8_t)original_reg_bank.load8(AL))}

// add eax, dword ptr [0x10200]
TEST(AddTest, Add03){ADDITION("add03.txt", reg_bank.load32(EAX),
                              original_reg_bank.load32(EAX) + 0x01a11001)}

// add al, 1
TEST(AddTest, Add04){
  ADDITION("add04.txt", reg_bank.load8(AL), original_reg_bank.load8(AL) + 0x01)}

// add eax, 0x10050301
TEST(AddTest, Add05){ADDITION("add05.txt", reg_bank.load32(EAX),
                              original_reg_bank.load32(EAX) + 0x10050301)}

// add al, 1
TEST(AddTest, Add80){
  ADDITION("add80.txt", reg_bank.load8(AL), original_reg_bank.load8(AL) + 0x01)}

// add ebx, 0x1001000
TEST(AddTest, Add81){
  ADDITION("add81.txt", (int32_t)reg_bank.load32(EBX),
           (int32_t)original_reg_bank.load32(EBX) + (int32_t)0x1001000)}

// add ebx, 0x1
TEST(AddTest, Add83) {
  ADDITION("add83.txt", reg_bank.load32(EBX),
           original_reg_bank.load32(EBX) + 0x1)
}
