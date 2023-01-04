#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <filesystem>

#define TEST_PATH std::filesystem::current_path().string() + "/res/"

#define ASSERT_X86_DEATH(path, err_msg)                                        \
  {                                                                            \
    Scanner scanner(OPCODE_TEST_PATH + path);                                  \
    RegisterBank reg_bank;                                                     \
    Memory memory;                                                             \
    Argument args{scanner, reg_bank, memory};                                  \
    ASSERT_DEATH({ parse(args); }, err_msg);                                   \
  }

#endif
