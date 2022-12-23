#include "sib.hpp"
#include <cmath>
#include <iostream>

uint32_t getScaledIndex(const uint8_t &scale, const uint8_t &index,
                        RegisterBank &regBank) {
  if (index == ESP) {
    std::cerr << "Register esp cannot be the index of the SIB byte"
              << std::endl;
    exit(1);
  }
  return regBank.load(index) * pow(2, scale);
}

uint32_t processSIB(const uint8_t &sib, RegisterBank &regBank) {
  const uint8_t base = sib & 0x07;
  const uint8_t index = (sib >> 3) & 0x07;
  const uint8_t scale = (sib >> 6) & 0x03;
  return regBank.load(base) + getScaledIndex(scale, index, regBank);
}
