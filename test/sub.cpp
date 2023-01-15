#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define SUB_TEST_PATH (TEST_PATH + "sub/")

#define SUBTRACTION(file_name, dest, expected)                                 \
  {                                                                            \
    INIT_STATE(SUB_TEST_PATH + file_name)                                      \
    std::string memory_change;                                                 \
    memory.store32(memory_change, 0x00010200, 0x01a11001);                     \
                                                                               \
    RegisterBank original_reg_bank = reg_bank;                                 \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(dest, expected);                                                 \
    ASSERT_EQ(state.snapshots.size(), 1);                                      \
  }

// sub bl, al
TEST(SubTest, Sub28){SUBTRACTION("sub28.txt", (int8_t)reg_bank.load8(BL),
                                 (int8_t)original_reg_bank.load8(BL) -
                                   (int8_t)original_reg_bank.load8(AL))}

// sub edi, ecx
TEST(SubTest, Sub29){SUBTRACTION("sub29.txt", (int32_t)reg_bank.load32(EDI),
                                 (int32_t)original_reg_bank.load32(EDI) -
                                   (int32_t)original_reg_bank.load32(ECX))}

// sub al, bl
TEST(SubTest, Sub2A){SUBTRACTION("sub2A.txt", (int8_t)reg_bank.load8(AL),
                                 (int8_t)original_reg_bank.load8(AL) -
                                   (int8_t)original_reg_bank.load8(BL))}

// sub eax, dword ptr [0x10200]
TEST(SubTest, Sub2B){
  SUBTRACTION("sub2B.txt", (int32_t)reg_bank.load32(EAX),
              (int32_t)original_reg_bank.load32(EAX) - (int32_t)0x01a11001)}

// sub al, 1
TEST(SubTest, Sub2C){SUBTRACTION("sub2C.txt", reg_bank.load8(AL),
                                 original_reg_bank.load8(AL) - 0x01)}

// sub eax, 0x10050301
TEST(SubTest, Sub2D){SUBTRACTION("sub2D.txt", reg_bank.load32(EAX),
                                 original_reg_bank.load32(EAX) - 0x10050301)}

// sub al, 1
TEST(SubTest, Sub80){SUBTRACTION("sub80.txt", (int8_t)reg_bank.load8(AL),
                                 (int8_t)original_reg_bank.load8(AL) - 0x01)}

// sub ebx, 0x1001000
TEST(SubTest, Sub81){
  SUBTRACTION("sub81.txt", (int32_t)reg_bank.load32(EBX),
              (int32_t)original_reg_bank.load32(EBX) - (int32_t)0x1001000)}

// sub ebx, 0x1
TEST(SubTest, Sub83) {
  SUBTRACTION("sub83.txt", (int32_t)reg_bank.load32(EBX),
              (int32_t)original_reg_bank.load32(EBX) - 0x1)
}
