#include "scanner.hpp"
#include "utils.hpp"

Scanner::Scanner(RegisterBank &reg_bank, Memory &memory, OperandSize mode)
  : m_reg_bank(reg_bank), m_memory(memory), m_mode(mode) {}

uint8_t Scanner::next_byte() {
  uint32_t ip = m_reg_bank.load_eip();
  uint8_t byte = m_memory.load8(ip);

  m_reg_bank.set_eip(ip + 1, m_mode);
  return byte;
}

uint32_t Scanner::next_nbytes(unsigned short num_bytes) {
  uint32_t val = 0;
  for (size_t i = 0; i < num_bytes; i++)
    val |= next_byte() << (8 * i);
  return val;
}

bool Scanner::is_eof() {
  return !m_memory.is_allocated(m_reg_bank.load_eip() - 1);
}
