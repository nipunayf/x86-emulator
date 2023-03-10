#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <filesystem>

#define TEST_PATH std::filesystem::current_path().string() + "/res/"

uint32_t store_program(const std::string &file_path, RegisterBank &reg_bank,
                       Memory &memory) {
  // Open the provided file path
  std::ifstream m_file;
  m_file.open(file_path);
  if (!m_file) {
    print_error_and_exit("Invalid file path: %s", file_path.c_str());
  }
  m_file >> std::hex;

  // Store the byte stream in the memory
  std::string transition;
  uint32_t eip = reg_bank.load_eip();
  uint16_t byte;
  while (m_file >> byte) {
    memory.store8(transition, eip, (uint8_t)byte);
    eip++;
  }
  return eip - 1;
}

#define INIT_STATE(test_path)                                                  \
  RegisterBank reg_bank;                                                       \
  Memory memory;                                                               \
  uint32_t last_eip = store_program(test_path, reg_bank, memory);              \
  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32, last_eip);      \
  State state{ins_fetcher, reg_bank, memory};

#endif
