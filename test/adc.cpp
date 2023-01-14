#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define ADC_TEST_PATH (TEST_PATH + "adc/")

#define INIT_STATE(test_path)                                                  \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  store_program(test_path, reg_bank, memory);                                  \
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);                \
  State state{ins_fetcher, reg_bank, memory};

#define ADDITION_CARRY(file_name, dest, expected)                              \
  {                                                                            \
    INIT_STATE(ADC_TEST_PATH + file_name)                                      \
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

// adc bl, al
TEST(AdcTest, Adc10){ADDITION_CARRY("adc10.txt", (int8_t)reg_bank.load8(BL),
                                    (int8_t)original_reg_bank.load8(AL) +
                                      (int8_t)original_reg_bank.load8(BL) + 1)}

// adc edi, ecx
TEST(AdcTest, Adc11){ADDITION_CARRY("adc11.txt", (int32_t)reg_bank.load32(ECX),
                                    (int32_t)original_reg_bank.load32(EDI) +
                                      (int32_t)original_reg_bank.load32(ECX))}

// adc al, bl
TEST(AdcTest, Adc12){ADDITION_CARRY("adc12.txt", (int8_t)reg_bank.load8(AL),
                                    (int8_t)original_reg_bank.load8(BL) +
                                      (int8_t)original_reg_bank.load8(AL) + 1)}

// adc eax, dword ptr [0x10200]
TEST(AdcTest,
     Adc13){ADDITION_CARRY("adc13.txt", reg_bank.load32(EAX),
                           original_reg_bank.load32(EAX) + 0x01a11001 + 1)}

// adc al, 1
TEST(AdcTest, Adc14){ADDITION_CARRY("adc14.txt", reg_bank.load8(AL),
                                    original_reg_bank.load8(AL) + 0x01 + 1)}

// adc eax, 0x10050301
TEST(AdcTest,
     Adc15){ADDITION_CARRY("adc15.txt", reg_bank.load32(EAX),
                           original_reg_bank.load32(EAX) + 0x10050301 + 1)}

// adc al, 1
TEST(AdcTest, Adc80){ADDITION_CARRY("adc80.txt", reg_bank.load8(AL),
                                    original_reg_bank.load8(AL) + 0x01 + 1)}

// adc ebx, 0x1001000
TEST(AdcTest, Adc81){ADDITION_CARRY("adc81.txt", (int32_t)reg_bank.load32(EBX),
                                    (int32_t)original_reg_bank.load32(EBX) +
                                      (int32_t)0x1001000 + 1)}

// adc ebx, 0x1
TEST(AdcTest, Adc83) {
  ADDITION_CARRY("adc83.txt", reg_bank.load32(EBX),
                 original_reg_bank.load32(EBX) + 0x1 + 1)
}
