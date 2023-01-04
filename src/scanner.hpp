#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>

class Scanner {
private:
  std::ifstream file;

public:
  Scanner(const std::string &file_path);

  ~Scanner();

  uint8_t next_byte();
  uint32_t next_four_bytes();
};

#endif
