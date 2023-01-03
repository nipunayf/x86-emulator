#include "sib.hpp"
#include <cmath>
#include <iostream>

uint32_t get_scaled_index(const uint8_t &scale, const uint8_t &index,
                          RegisterBank &reg_bank) {
  if (index == ESP) {
    std::cerr << "Register esp cannot be the index of the SIB byte"
              << std::endl;
    exit(1);
  }
  return reg_bank.load(index) * pow(2, scale);
}

uint32_t process_sib(const uint8_t &sib, RegisterBank &reg_bank) {
  const uint8_t base = sib & 0x07;
  const uint8_t index = (sib >> 3) & 0x07;
  const uint8_t scale = (sib >> 6) & 0x03;
  return reg_bank.load(base) + get_scaled_index(scale, index, reg_bank);
}
