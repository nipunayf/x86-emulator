#include "register_bank.hpp"

#define MASK_32 4294967295 << 32
#define MASK_16 (MASK_32 | (65535 << 16))
#define MASK_L8 (MASK_16 | (255 << 8))
#define MASK_H8 (MASK_16 | 255)

RegisterBank::RegisterBank() {
  m_registers[RAX] = Register({0xbf8db144, "%ax", "%eax", "%rax"});
  m_registers[RCX] = Register({0x88c5cffb, "%cx", "%ecx", "%rcx"});
  m_registers[RDX] = Register({0x1, "%dx", "%edx", "%rdx"});
  m_registers[RBX] = Register({0xae5ff4, "%bx", "%ebx", "%rbx"});
  m_registers[RSP] = Register({0xbf8db0bc, "%sp", "%esp", "%rsp"});
  m_registers[RBP] = Register({0xbf8db118, "%bp", "%ebp", "%rbp"});
  m_registers[RSI] = Register({0x9a0ca0, "%si", "%esi", "%rsi"});
  m_registers[RDI] = Register({0x0, "%di", "%edi", "%rdi"});
}

std::string RegisterBank::name16(const uint32_t &index) {
  return m_registers[index].name16;
}

std::string RegisterBank::name32(const uint32_t &index) {
  return m_registers[index].name32;
}

std::string RegisterBank::name64(const uint32_t &index) {
  return m_registers[index].name64;
}

uint16_t RegisterBank::load16(const uint32_t &index) {
  return m_registers[index].value;
}

uint32_t RegisterBank::load32(const uint32_t &index) {
  return m_registers[index].value;
}

uint64_t RegisterBank::load64(const uint32_t &index) {
  return m_registers[index].value;
}

void RegisterBank::set8(const uint32_t &index, const uint8_t value) {
  if (index % 2 == 1)
    m_registers[index / 2].value = (m_registers[index].value & MASK_L8) | value;
  else
    m_registers[index / 2].value = (m_registers[index].value & MASK_H8) | value;
}

void RegisterBank::set16(const uint32_t &index, const uint16_t value) {
  m_registers[index].value = (m_registers[index].value & MASK_16) | value;
}

void RegisterBank::set32(const uint32_t &index, const uint32_t value) {
  m_registers[index].value = (m_registers[index].value & MASK_32) | value;
}

void RegisterBank::set64(const uint32_t &index, const uint64_t value) {
  m_registers[index].value = value;
}

void RegisterBank::set_flag(const FLAG &flag, uint8_t val) {
  m_eflags |= val << flag;
}

uint8_t RegisterBank::get_flag(const FLAG &flag) {
  return (m_eflags >> flag) & 1;
}
