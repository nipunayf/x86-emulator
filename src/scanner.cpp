#include "scanner.hpp"
#include <iostream>

Scanner::Scanner(const std::string &file_path) {
  m_file.open(file_path);
  if (!m_file) {
    std::cerr << "Invalid file path: " << file_path << std::endl;
    exit(1);
  }
  m_file >> std::hex;
}

Scanner::~Scanner() { m_file.close(); }

uint8_t Scanner::next_byte() {
  uint16_t byte;
  if (m_file >> byte)
    return (uint8_t)byte;
  return 0;
}

uint32_t Scanner::next_nbytes(unsigned short num_bytes) {
  uint32_t val = 0;
  for (size_t i = 0; i < num_bytes; i++)
    val |= next_byte() << (8 * i);
  return val;
}
