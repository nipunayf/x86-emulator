#include "instruction_fetcher.hpp"
#include "utils.hpp"

InstructionFetcher::InstructionFetcher(RegisterBank &reg_bank, Memory &memory,
                                       OperandSize mode)
  : m_reg_bank(reg_bank), m_memory(memory), m_mode(mode) {}

uint8_t InstructionFetcher::fetch_instruction(int32_t offset) {
  uint32_t current_eip = m_reg_bank.load_eip();
  uint8_t byte = m_memory.load8(current_eip + offset);
  m_reg_bank.set_eip(current_eip + offset + 1, m_mode);
  return byte;
}

uint8_t InstructionFetcher::next_byte() { return fetch_instruction(0); }

uint32_t InstructionFetcher::next_nbytes(unsigned short num_bytes) {
  uint32_t val = 0;
  for (size_t i = 0; i < num_bytes; i++)
    val |= next_byte() << (8 * i);
  return val;
}

void InstructionFetcher::jump_byte(int32_t offset) {
  fetch_instruction(offset - 1);
}

bool InstructionFetcher::is_eof() {
  return !m_memory.is_allocated(m_reg_bank.load_eip() - 1);
}
