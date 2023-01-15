#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define FLAGS_TEST_PATH (TEST_PATH + "flags/")

// stc
// clc
// cmc
TEST(FlagTest, FlagCF) {
  INIT_STATE(FLAGS_TEST_PATH + "cf.txt")
  parse(state);

  std::string operations[] = {"stc", "clc", "cmc"};
  std::string expected_flag_transitions[] = {
    "CF(0x0) -> (0x1)", "CF(0x1) -> (0x0)", "CF(0x0) -> (0x1)"};

  ASSERT_EQ(state.snapshots.size(), 3);
  int index = 0;
  for (Snapshot snapshot : state.snapshots) {
    auto flag_transition = snapshot.flag_transitions.begin();
    ASSERT_STREQ(flag_transition->c_str(),
                 expected_flag_transitions[index].c_str());
    ASSERT_STREQ(snapshot.instruction.c_str(), operations[index].c_str());
    index++;
  }
}
