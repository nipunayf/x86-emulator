#include "memory.hpp"
#include "dump.hpp"
#include <iostream>

void Memory::store(std::string &transition, const uint32_t &address,
                   const uint32_t &data, const OperandSize &size) {
  uint32_t prev_value = load(address, size);
  uint8_t nbytes = 1 << size;
  for (uint8_t i = 0; i < nbytes; i++)
    m_buffer[address + i] = (data >> 8 * i) & MASK8;
  transition =
    format_register_change("#" + format_hex_string(address), prev_value, data);
}

void Memory::store8(std::string &transition, const uint32_t &address,
                    const uint8_t &data) {
  store(transition, address, data, OPERAND_8);
}

void Memory::store16(std::string &transition, const uint32_t &address,
                     const uint16_t &data) {
  store(transition, address, data, OPERAND_16);
}

void Memory::store32(std::string &transition, const uint32_t &address,
                     const uint32_t &data) {
  store(transition, address, data, OPERAND_32);
}

uint32_t Memory::load(const uint32_t &address, const OperandSize &size) {
  uint8_t nbytes = 1 << size;
  if (m_buffer.count(address)) {
    uint32_t val = 0;
    for (uint8_t i = 0; i < nbytes; i++)
      val |= (m_buffer[address + i] << 8 * i);
    return val;
  }
  return 0;
}

uint8_t Memory::load8(const uint32_t &address) {
  return load(address, OPERAND_8);
}

uint16_t Memory::load16(const uint32_t &address) {
  return load(address, OPERAND_16);
}

uint32_t Memory::load32(const uint32_t &address) {
  return load(address, OPERAND_32);
}

void Memory::memory_dump(uint32_t start_eip, uint32_t end_eip) {
  std::cout << "========MEMORY DUMP========" << std::endl;
  for (auto const &loc : m_buffer) {
    if (loc.first < start_eip || loc.first > end_eip)
      table_row_printer(format_hex_string(loc.first), 12,
                        format_hex_string(loc.second), 12);
  }
  std::cout << std::endl;
}
