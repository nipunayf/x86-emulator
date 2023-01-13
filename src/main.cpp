#include "iostream"
#include "opcode.hpp"

int main(int argc, char *argv[]) {
  // Parse the input arguments
  std::string file_path = argc > 1 ? argv[1] : "";

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

  InstructionFetcher ins_fetcher(reg_bank, memory, OPERAND_32);
  State state{ins_fetcher, reg_bank, memory};
  parse(state);

  return 0;
}
