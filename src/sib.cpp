#include "sib.hpp"
#include <iostream>

uint32_t get_scaled_index(const uint8_t &scale, const uint8_t &index,
                          RegisterBank &reg_bank) {
  if (index == ESP)
    print_error_and_exit("Register esp cannot be the index of the SIB byte");
  return (uint32_t)(reg_bank.load32(index) * scale);
}

uint32_t process_sib(const uint8_t &sib, RegisterBank &reg_bank,
                     std::string &name, uint32_t displacement) {
  const uint8_t base = sib & 0x07;
  const uint8_t index = (sib >> 3) & 0x07;
  const uint8_t scale = 1 << ((sib >> 6) & 0x03);
  name = format_sib(reg_bank.name32(base), reg_bank.name32(index), scale,
                    displacement);
  return reg_bank.load32(base) + get_scaled_index(scale, index, reg_bank) +
         displacement;
}
