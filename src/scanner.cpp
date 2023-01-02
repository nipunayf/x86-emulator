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

uint8_t Scanner::next() {
  uint16_t byte;
  if (file >> byte) {
    return (uint8_t)byte;
  }
  return 0;
}
