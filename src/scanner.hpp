#ifndef SCANNER_H
#define SCANNER_H

#include "register_bank.hpp"
#include <fstream>
#include <string>

class Scanner {
private:
  std::ifstream m_file;

public:
  explicit Scanner(const std::string &file_path);

  ~Scanner();

  uint8_t next_byte(RegisterBank &reg_bank, OperandSize mode);
  uint32_t next_nbytes(unsigned short num_bytes, RegisterBank &reg_bank,
                       OperandSize mode);
  bool is_eof();
};

#endif
