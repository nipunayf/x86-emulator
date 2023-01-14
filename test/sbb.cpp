#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define SBB_TEST_PATH (TEST_PATH + "sbb/")

#define SUBTRACTION_BORROW(file_name, dest, expected)                          \
  {                                                                            \
    INIT_STATE(SBB_TEST_PATH + file_name)                                      \
    std::string memory_change;                                                 \
    memory.store32(memory_change, 0x00010200, 0x01a11001);                     \
    std::list<std::string> flag_transitions;                                   \
    reg_bank.set_flag(flag_transitions, CF, 1);                                \
                                                                               \
    RegisterBank original_reg_bank = reg_bank;                                 \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(dest, expected);                                                 \
    ASSERT_EQ(state.snapshots.size(), 1);                                      \
  }

// sbb bl, al
TEST(SbbTest,
     Sbb18){SUBTRACTION_BORROW("sbb18.txt", (int8_t)reg_bank.load8(BL),
                               (int8_t)original_reg_bank.load8(BL) -
                                 (int8_t)original_reg_bank.load8(AL) - 1)}

// sbb edi, ecx
TEST(SbbTest,
     Sbb19){SUBTRACTION_BORROW("sbb19.txt", (int32_t)reg_bank.load32(EDI),
                               (int32_t)original_reg_bank.load32(EDI) -
                                 (int32_t)original_reg_bank.load32(ECX) - 1)}

// sbb al, bl
TEST(SbbTest,
     Sbb1A){SUBTRACTION_BORROW("sbb1A.txt", (int8_t)reg_bank.load8(AL),
                               (int8_t)original_reg_bank.load8(AL) -
                                 (int8_t)original_reg_bank.load8(BL) - 1)}

// sbb eax, dword ptr [0x10200]
TEST(SbbTest,
     Sbb1B){SUBTRACTION_BORROW("sbb1B.txt", (int32_t)reg_bank.load32(EAX),
                               (int32_t)original_reg_bank.load32(EAX) -
                                 (int32_t)0x01a11001 - 1)}

// sbb al, 1
TEST(SbbTest, Sbb1C){SUBTRACTION_BORROW("sbb1C.txt", reg_bank.load8(AL),
                                        original_reg_bank.load8(AL) - 0x01 - 1)}

// sbb eax, 0x10050301
TEST(SbbTest,
     Sbb1D){SUBTRACTION_BORROW("sbb1D.txt", reg_bank.load32(EAX),
                               original_reg_bank.load32(EAX) - 0x10050301 - 1)}

// sbb al, 1
TEST(SbbTest,
     Sbb80){SUBTRACTION_BORROW("sbb80.txt", (int8_t)reg_bank.load8(AL),
                               (int8_t)original_reg_bank.load8(AL) - 0x01 - 1)}

// sbb ebx, 0x1001000
TEST(SbbTest,
     Sbb81){SUBTRACTION_BORROW("sbb81.txt", (int32_t)reg_bank.load32(EBX),
                               (int32_t)original_reg_bank.load32(EBX) -
                                 (int32_t)0x1001000 - 1)}

// sbb ebx, 0x1
TEST(SbbTest, Sbb83) {
  SUBTRACTION_BORROW("sbb83.txt", (int32_t)reg_bank.load32(EBX),
                     (int32_t)original_reg_bank.load32(EBX) - 0x1 - 1)
}
