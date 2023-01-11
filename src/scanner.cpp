#include "scanner.hpp"
#include "utils.hpp"
#include <iostream>

Scanner::Scanner(const std::string &file_path) {
  m_file.open(file_path);
  if (!m_file)
    print_error_and_exit("Invalid file path: %s", file_path.c_str());
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

bool Scanner::is_eof() { return m_file.peek() == EOF; }
