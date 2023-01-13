#ifndef SCANNER_H
#define SCANNER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include <fstream>
#include <string>

class Scanner {
private:
  RegisterBank &m_reg_bank;
  Memory &m_memory;
  OperandSize m_mode;

public:
  Scanner(RegisterBank &reg_bank, Memory &memory, OperandSize mode);

  uint8_t next_byte();
  uint32_t next_nbytes(unsigned short num_bytes);
  bool is_eof();
};

#endif
