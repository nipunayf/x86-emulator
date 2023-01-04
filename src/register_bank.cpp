#include "register_bank.hpp"

#define MASK_32 4294967295 << 32
#define MASK_16 MASK_32 | (65535 << 16)
#define MASK_L8 MASK_16 | (255 << 8)
#define MASK_H8 MASK_16 | 255

RegisterBank::RegisterBank() {
  registers[RAX] = Register({0xbf8db144, "ah", "ax", "eax", "rax"});
  registers[RCX] = Register({0x88c5cffb, "al", "cx", "ecx", "rcx"});
  registers[RDX] = Register({0x1, "ch", "dx", "edx", "rdx"});
  registers[RBX] = Register({0xae5ff4, "cl", "bx", "ebx", "rbx"});
  registers[RSP] = Register({0xbf8db0bc, "dh", "sp", "esp", "rsp"});
  registers[RBP] = Register({0xbf8db118, "dl", "bp", "ebp", "rbp"});
  registers[RSI] = Register({0x9a0ca0, "bh", "si", "esi", "rsi"});
  registers[RDI] = Register({0x0, "bl", "di", "edi", "rdi"});
}

std::string RegisterBank::name8(const uint32_t &index) {
  return registers[index].name8;
}

std::string RegisterBank::name16(const uint32_t &index) {
  return registers[index].name16;
}

std::string RegisterBank::name32(const uint32_t &index) {
  return registers[index].name32;
}
std::string RegisterBank::name64(const uint32_t &index) {
  return registers[index].name64;
}

uint16_t RegisterBank::load16(const uint32_t &index) {
  return registers[index].value;
}

uint32_t RegisterBank::load32(const uint32_t &index) {
  return registers[index].value;
}

uint64_t RegisterBank::load64(const uint32_t &index) {
  return registers[index].value;
}

void RegisterBank::set8(const uint32_t &index, const uint8_t value) {
  if (index % 2 == 1)
    registers[index / 2].value = (registers[index].value & MASK_L8) | value;
  else
    registers[index / 2].value = (registers[index].value & MASK_H8) | value;
}

void RegisterBank::set16(const uint32_t &index, const uint16_t value) {
  registers[index].value = (registers[index].value & MASK_16) | value;
}

void RegisterBank::set32(const uint32_t &index, const uint32_t value) {
  registers[index].value = (registers[index].value & MASK_32) | value;
}

void RegisterBank::set64(const uint32_t &index, const uint64_t value) {
  registers[index].value = value;
}
