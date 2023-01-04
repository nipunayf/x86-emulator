#include "scanner.hpp"
#include <iostream>

Scanner::Scanner(const std::string &file_path) {
  this->file.open(file_path);
  if (!this->file) {
    std::cerr << "Invalid file path: " << file_path << std::endl;
    exit(1);
  }
  this->file >> std::hex;
}

Scanner::~Scanner() { this->file.close(); }

uint8_t Scanner::next_byte() {
  uint16_t byte;
  if (file >> byte)
    return (uint8_t)byte;
  return 0;
}

uint32_t Scanner::next_four_bytes() {
  uint32_t val = 0;
  uint8_t byte;
  for (size_t i = 0; i < 4; i++)
    val |= next_byte() << (8 * i);
  return val;
}
