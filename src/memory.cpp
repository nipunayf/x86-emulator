#include "memory.hpp"

void Memory::store(const uint32_t &address, const uint32_t &data) {
  buffer[address] = data;
}

uint32_t Memory::read(const uint32_t &address) {
  if (buffer.count(address))
    return buffer[address];
  return 0;
}
