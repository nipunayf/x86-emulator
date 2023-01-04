#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define OPCODE_TEST_PATH (TEST_PATH + "/opcode/")

TEST(OpcodeTest, InvalidOneByte) {
  Scanner scanner(OPCODE_TEST_PATH + "invalid_1byte.txt");
  ASSERT_DEATH({ parse(scanner); },
               "Invalid opcode: 0x99 is not yet supported");
}

TEST(OpcodeTest, InvalidTwoBytes) {
  Scanner scanner(OPCODE_TEST_PATH + "invalid_2bytes.txt");
  ASSERT_DEATH({ parse(scanner); },
               "Invalid opcode bytes: 2 is not yet supported");
}

TEST(OpcodeTest, InvalidThreeBytes) {
  Scanner scanner(OPCODE_TEST_PATH + "invalid_3bytes.txt");
  ASSERT_DEATH({ parse(scanner); },
               "Invalid opcode bytes: 3 is not yet supported");
}

TEST(OpcodeTest, InvalidSecondByteOfFourBytes) {
  Scanner scanner(OPCODE_TEST_PATH + "invalid_2byte_4bytes.txt");
  ASSERT_DEATH({ parse(scanner); }, "Expected 0xf after 0x66");
}

TEST(OpcodeTest, ValidOneByte) {
  Scanner scanner(OPCODE_TEST_PATH + "valid_1byte.txt");
  ASSERT_FALSE(parse(scanner));
}
