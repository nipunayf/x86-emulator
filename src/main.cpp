#include "opcode.hpp"
#include <iomanip>
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
  // Parse the input arguments
  std::string file_path = argc > 1 ? argv[1] : "";
  bool enable_step =
    argc > 2 ? strcmp(argv[2], "--enable-step") ? false : true : false;

  // Initialize the memory
  RegisterBank reg_bank;
  Memory memory;

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

  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32, eip - 1);
  State state{ins_fetcher, reg_bank, memory};
  parse(state, enable_step);
  reg_bank.register_dump();
  memory.memory_dump();
  std::cout << "INSTRUCTIONS" << std::endl;
  for (Snapshot s : state.snapshots) {
    std::cout << std::setw(12) << std::left << s.byte_sequence;
    std::cout << s.instruction << std::endl;
  }
  std::cout << std::endl;

  return 0;
}
