#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define CMP_TEST_PATH (TEST_PATH + "cmp/")

#define CMP(file_name, zf_flag)                                                \
  {                                                                            \
    INIT_STATE(CMP_TEST_PATH + file_name)                                      \
    parse(state);                                                              \
                                                                               \
    ASSERT_EQ(reg_bank.load_flag(ZF), zf_flag);                                \
  }

TEST(CmpTest, Cmp3C){CMP("cmp3C.txt", 1)}

TEST(CmpTest, Cmp3D){CMP("cmp3D.txt", 0)}

TEST(CmpTest, Cmp39){CMP("cmp39.txt", 1)}

TEST(CmpTest, Cmp83) {
  CMP("cmp83.txt", 0)
}
