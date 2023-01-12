#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define OPCODE_TEST_PATH (TEST_PATH + "opcode/")

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
  Scanner scanner(OPCODE_TEST_PATH + "valid_1byte.txt");
  RegisterBank reg_bank;
  Memory memory;
  State state{scanner, reg_bank, memory};
  ASSERT_FALSE(parse(state));
}
