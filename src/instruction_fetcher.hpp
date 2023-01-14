#ifndef INSTRUCTION_FETCHER_H
#define INSTRUCTION_FETCHER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include <fstream>
#include <sstream>
#include <string>

class InstructionFetcher {
private:
  RegisterBank &m_reg_bank;
  Memory &m_memory;
  OperandSize m_mode;
  uint32_t m_last_eip;
  std::stringstream m_byte_sequence;

public:
  InstructionFetcher(RegisterBank &reg_bank, Memory &memory, OperandSize mode,
                     uint32_t last_eip);

  uint8_t next_byte();
  uint32_t next_nbytes(unsigned short num_bytes);
  void jump_byte(int32_t offset);
  void set_last_eip(uint32_t last_eip);
  bool is_eof();
  std::string get_byte_sequence();
};

#endif
