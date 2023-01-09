#include "register_bank.hpp"

#define MASK_32 4294967295 << 32
#define MASK_16 (MASK_32 | (65535 << 16))
#define MASK_L8 (MASK_16 | (255 << 8))
#define MASK_H8 (MASK_16 | 255)

RegisterBank::RegisterBank() {
  m_registers[RAX] =
    Register({0xbf8db144, "%rax", "%eax", "%ax", "%ah", "%al"});
  m_registers[RCX] =
    Register({0x88c5cffb, "%rcx", "%ecx", "%cx", "%ch", "%cl"});
  m_registers[RDX] = Register({0x1, "%rdx", "%edx", "%dx", "%dh", "%dl"});
  m_registers[RBX] = Register({0xae5ff4, "%rbx", "%ebx", "%bx", "%bh", "%bl"});
  m_registers[RSP] = Register({0xbf8db0bc, "%rsp", "%esp", "%sp"});
  m_registers[RBP] = Register({0xbf8db118, "%rbp", "%ebp", "%bp"});
  m_registers[RSI] = Register({0x9a0ca0, "%rsi", "%esi", "%si"});
  m_registers[RDI] = Register({0x0, "%rdi", "%edi", "%di"});
}

std::string RegisterBank::name8(const uint32_t &index) {
  if (index > 3)
    return m_registers[index % 4].name8_h;
  return m_registers[index].name8_l;
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

std::string RegisterBank::name(const uint32_t &index, const OperandSize &size) {
  switch (size) {
  case OPERAND_8:
    return name8(index);
  case OPERAND_16:
    return name16(index);
  case OPERAND_32:
    return name32(index);
  case OPERAND_64:
    return name64(index);
  }
}

uint8_t RegisterBank::load8(const uint32_t &index) {
  if (index > 3)
    return m_registers[index % 4].value >> 8;
  else
    return m_registers[index].value;
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

uint64_t RegisterBank::load(const uint32_t &index, const OperandSize &size) {
  switch (size) {
  case OPERAND_8:
    return load8(index);
  case OPERAND_16:
    return load16(index);
  case OPERAND_32:
    return load32(index);
  case OPERAND_64:
    return load64(index);
  }
}

void RegisterBank::set8(const uint32_t &index, const uint8_t value) {
  if (index > 3)
    m_registers[index % 4].value =
      (m_registers[index % 4].value & MASK_H8) | value;
  else
    m_registers[index].value = (m_registers[index].value & MASK_L8) | value;
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

void RegisterBank::set(const uint32_t &index, const uint64_t value,
                       const OperandSize &size) {
  switch (size) {
  case OPERAND_8:
    set8(index, value);
  case OPERAND_16:
    set16(index, value);
  case OPERAND_32:
    set32(index, value);
  case OPERAND_64:
    set64(index, value);
  }
}

void RegisterBank::set_flag(const FLAG &flag, uint8_t val) {
  m_eflags |= val << flag;
}

uint8_t RegisterBank::get_flag(const FLAG &flag) {
  return (m_eflags >> flag) & 1;
}
