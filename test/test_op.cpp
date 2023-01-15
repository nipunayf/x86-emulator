#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define TEST_OP_TEST_PATH (TEST_PATH + "test/")

#define TEST_OP(file_name, zf_flag, sf_flag)                                   \
  {                                                                            \
    INIT_STATE(TEST_OP_TEST_PATH + file_name)                                  \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(reg_bank.load_flag(ZF), zf_flag);                                \
    ASSERT_EQ(reg_bank.load_flag(SF), sf_flag);                                \
  }

TEST(Test_Op_Test, TestA9){TEST_OP("testA9.txt", 0, 0)}

TEST(Test_Op_Test, TestF7){TEST_OP("testF7.txt", 0, 1)}

TEST(Test_Op_Test, Test85) {
  TEST_OP("test85.txt", 1, 0)
}
