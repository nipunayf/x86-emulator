#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define LEA_TEST_PATH (TEST_PATH + "lea/")

#define LEA(file_name, dest, expected)                                         \
  INIT_STATE(LEA_TEST_PATH + file_name)                                        \
  parse(state);                                                                \
                                                                               \
  ASSERT_EQ(dest, expected);                                                   \
  ASSERT_EQ(state.snapshots.size(), 1);

TEST(LeaTest, Lea8A) {
  LEA("lea8D.txt", reg_bank.load32(ECX), reg_bank.load32(ESP) + 4)
}
