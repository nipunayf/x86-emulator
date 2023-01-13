#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define OPCODE_TEST_PATH (TEST_PATH + "opcode/")

#define ASSERT_X86_DEATH(file_name, err_msg)                                   \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  store_program(OPCODE_TEST_PATH + file_name, reg_bank, memory);               \
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);                \
  State state{ins_fetcher, reg_bank, memory};                                  \
  ASSERT_DEATH({ parse(state); }, err_msg);

TEST(OpcodeTest, InvalidOneByte){
  ASSERT_X86_DEATH("invalid_1byte.txt",
                   "Invalid opcode: 0x99 is not yet supported")}

TEST(OpcodeTest, InvalidTwoBytes){
  ASSERT_X86_DEATH("invalid_2bytes.txt",
                   "Invalid opcode: 0x99 is not yet supported")}

TEST(OpcodeTest, InvalidThreeBytes){
  ASSERT_X86_DEATH("invalid_3bytes.txt",
                   "3-byte opcode bytes are not yet supported")}

TEST(OpcodeTest, ValidOneByte) {
  RegisterBank reg_bank;
  Memory memory;
  store_program(OPCODE_TEST_PATH + "valid_1byte.txt", reg_bank, memory);
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);
  State state{ins_fetcher, reg_bank, memory};
  ASSERT_FALSE(parse(state));
}
