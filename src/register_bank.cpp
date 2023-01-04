#include "register_bank.hpp"

#define MASK_32 4294967295 << 32
#define MASK_16 MASK_32 | (65535 << 16)
#define MASK_L8 MASK_16 | (255 << 8)
#define MASK_H8 MASK_16 | 255

RegisterBank::RegisterBank() {
  registers[RAX] = Register({"rax", 0xbf8db144});
  registers[RCX] = Register({"rcx", 0x88c5cffb});
  registers[RDX] = Register({"rdx", 0x1});
  registers[RBX] = Register({"rbx", 0xae5ff4});
  registers[RSP] = Register({"rsp", 0xbf8db0bc});
  registers[RBP] = Register({"rbp", 0xbf8db118});
  registers[RSI] = Register({"rsi", 0x9a0ca0});
  registers[RDI] = Register({"rdi", 0x0});
}

uint64_t RegisterBank::load64(const uint32_t &index) {
  return registers[index].value;
}

uint32_t RegisterBank::load32(const uint32_t &index) {
  return registers[index].value;
}

uint16_t RegisterBank::load16(const uint32_t &index) {
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
