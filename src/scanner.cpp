#include "scanner.hpp"
#include <iostream>

Scanner::Scanner(const std::string &file_path) {
  this->file.open(file_path);
  if (!this->file) {
    std::cerr << "Invalid file path: " << file_path << std::endl;
    exit(0);
  }
  this->file >> std::hex;
}

Scanner::~Scanner() { this->file.close(); }

uint16_t Scanner::next() {
  uint16_t nextByte;
  if (file >> nextByte) {
    return nextByte;
  }
  return 0;
}
