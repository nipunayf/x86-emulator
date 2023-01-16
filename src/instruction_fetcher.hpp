#ifndef INSTRUCTION_FETCHER_H
#define INSTRUCTION_FETCHER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include <fstream>
#include <sstream>
#include <string>

/**
 * Fetches the instruction from the memory
 */
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

  /**
   * Fetches the next byte.
   *
   * @return the next byte
   */
  uint8_t next_byte();

  /**
   * Fetches the next n bytes
   *
   * @param num_bytes number of bytes to be fetched
   * @return all the values as an integer
   */
  uint32_t next_nbytes(unsigned short num_bytes);

  /**
   * Add the offset to the instruction pointer
   *
   * @param offset amount of change
   */
  void jump_byte(int32_t offset);

  void set_last_eip(uint32_t last_eip);

  /**
   * Check if the emulator reached the end of hte file
   *
   * @return True if the emulator reaches the end of the file.
   */
  bool is_eof();

  /**
   * Obtain the byte sequence of an instruction.
   *
   * @return byte sequence as a string
   */
  std::string get_byte_sequence();
};

#endif
