#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>

class Scanner {
private:
  std::ifstream m_file;

public:
  explicit Scanner(const std::string &file_path);

  ~Scanner();

  uint8_t next_byte();
  uint32_t next_nbytes(unsigned short num_bytes);
  bool is_eof();
};

#endif
