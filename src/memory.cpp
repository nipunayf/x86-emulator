#include "memory.hpp"

void Memory::store(std::string &transition, const uint32_t &address,
                   const uint32_t &data) {
  uint32_t prev_value = read(address);
  buffer[address] = data;
  transition =
    format_register_change("#" + format_hex_string(address), prev_value, data);
}

uint32_t Memory::read(const uint32_t &address) {
  if (buffer.count(address))
    return buffer[address];
  return 0;
}
