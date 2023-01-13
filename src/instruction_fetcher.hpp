#ifndef INSTRUCTION_FETCHER_H
#define INSTRUCTION_FETCHER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include <fstream>
#include <string>

class InstructionFetcher {
private:
  RegisterBank &m_reg_bank;
  Memory &m_memory;
  OperandSize m_mode;

  uint8_t fetch_instruction(uint32_t offset);

public:
  InstructionFetcher(RegisterBank &reg_bank, Memory &memory, OperandSize mode);

  uint8_t next_byte();
  uint32_t next_nbytes(unsigned short num_bytes);
  void jump_byte(uint32_t offset);
  bool is_eof();
};

#endif
