#include "register_bank.hpp"

#define MASK_32 4294967295 << 32
#define MASK_16 (MASK_32 | (65535 << 16))
#define MASK_L8 (MASK_16 | (255 << 8))
#define MASK_H8 (MASK_16 | 255)

std::map<FLAG, std::string> flag_name_map = {
  {CF, "CF"}, {PF, "PF"}, {AF, "AF"},   {ZF, "ZF"},     {SF, "SF"}, {TF, "TF"},
  {IF, "IF"}, {DF, "DF"}, {OF, "OF"},   {IOPL, "IOPL"}, {NT, "NT"}, {RF, "RF"},
  {VM, "VM"}, {AC, "AC"}, {VIF, "VIF"}, {VIP, "VIP"},   {ID, "ID"}};

RegisterBank::RegisterBank() {
  m_gp_registers[RAX] =
    GPRegister({0xbf8db144, "%rax", "%eax", "%ax", "%ah", "%al"});
  m_gp_registers[RCX] =
    GPRegister({0x88c5cffb, "%rcx", "%ecx", "%cx", "%ch", "%cl"});
  m_gp_registers[RDX] = GPRegister({0x1, "%rdx", "%edx", "%dx", "%dh", "%dl"});
  m_gp_registers[RBX] =
    GPRegister({0xae5ff4, "%rbx", "%ebx", "%bx", "%bh", "%bl"});
  m_gp_registers[RSP] = GPRegister({0xbf8db0bc, "%rsp", "%esp", "%sp"});
  m_gp_registers[RBP] = GPRegister({0xbf8db118, "%rbp", "%ebp", "%bp"});
  m_gp_registers[RSI] = GPRegister({0x9a0ca0, "%rsi", "%esi", "%si"});
  m_gp_registers[RDI] = GPRegister({0x0, "%rdi", "%edi", "%di"});

  m_seg_registers[CS] = SegRegister({0x73, "%cs"});
  m_seg_registers[SS] = SegRegister({0x7b, "%ss"});
  m_seg_registers[DS] = SegRegister({0x7b, "%ds"});
  m_seg_registers[ES] = SegRegister({0x7b, "%es"});
  m_seg_registers[FS] = SegRegister({0x0, "%fs"});
  m_seg_registers[GS] = SegRegister({0x33, "%gs"});

  m_eip = InstructionPointer({0x8048354, "%rip", "%eip", "%ip"});
}

std::string RegisterBank::name8(const uint32_t &index) {
  if (index > 3)
    return m_gp_registers[index % 4].name8_h;
  return m_gp_registers[index].name8_l;
}

std::string RegisterBank::name16(const uint32_t &index) {
  return m_gp_registers[index].name16;
}

std::string RegisterBank::name32(const uint32_t &index) {
  return m_gp_registers[index].name32;
}

std::string RegisterBank::name64(const uint32_t &index) {
  return m_gp_registers[index].name64;
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
    return m_gp_registers[index % 4].value >> 8;
  else
    return m_gp_registers[index].value;
}

uint16_t RegisterBank::load16(const uint32_t &index) {
  return m_gp_registers[index].value;
}

uint32_t RegisterBank::load32(const uint32_t &index) {
  return m_gp_registers[index].value;
}

uint64_t RegisterBank::load64(const uint32_t &index) {
  return m_gp_registers[index].value;
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

void RegisterBank::set8(std::string &transition, const uint32_t &index,
                        const uint8_t value) {
  uint8_t prev_value = load8(index);
  if (index > 3)
    m_gp_registers[index % 4].value =
      (m_gp_registers[index % 4].value & MASK_H8) | value;
  else
    m_gp_registers[index].value =
      (m_gp_registers[index].value & MASK_L8) | value;
  transition = format_register_change(name8(index), prev_value, value);
}

void RegisterBank::set16(std::string &transition, const uint32_t &index,
                         const uint16_t value) {
  uint8_t prev_value = load16(index);
  m_gp_registers[index].value = (m_gp_registers[index].value & MASK_16) | value;
  transition = format_register_change(name16(index), prev_value, value);
}

void RegisterBank::set32(std::string &transition, const uint32_t &index,
                         const uint32_t value) {
  uint8_t prev_value = load32(index);
  m_gp_registers[index].value = (m_gp_registers[index].value & MASK_32) | value;
  transition = format_register_change(name32(index), prev_value, value);
}

void RegisterBank::set64(std::string &transition, const uint32_t &index,
                         const uint64_t value) {
  uint8_t prev_value = load64(index);
  m_gp_registers[index].value = value;
  transition = format_register_change(name64(index), prev_value, value);
}

void RegisterBank::set(std::string &transition, const uint32_t &index,
                       const uint64_t value, const OperandSize &size) {
  switch (size) {
  case OPERAND_8:
    set8(transition, index, value);
  case OPERAND_16:
    set16(transition, index, value);
  case OPERAND_32:
    set32(transition, index, value);
  case OPERAND_64:
    set64(transition, index, value);
  }
}

std::string name_flag(const FLAG &flag) { return flag_name_map[flag]; }

uint8_t RegisterBank::load_flag(const FLAG &flag) {
  return (m_eflags >> flag) & 1ul;
}

void RegisterBank::set_flag(std::list<std::string> &transitions,
                            const FLAG &flag, uint8_t val) {
  uint8_t prev_value = load_flag(flag);
  val == 0 ? m_eflags &= ~(1ul << flag) : m_eflags |= 1ul << flag;
  transitions.push_back(
    prev_value == val
      ? ""
      : format_register_change(name_flag(flag), prev_value, val));
}

std::string RegisterBank::name_seg(const uint32_t &index) {
  return m_seg_registers[index].name;
}

uint16_t RegisterBank::load_seg(const uint32_t &index) {
  return m_seg_registers[index].value;
}

void RegisterBank::set_seg(std::string &transition, const uint32_t &index,
                           const uint16_t value) {
  uint16_t prev_value = load_seg(index);
  m_seg_registers[index].value = value;
  transition = format_register_change(name_seg(index), prev_value, value);
}

uint64_t RegisterBank::load_eip() { return m_eip.value; }

void RegisterBank::set_eip(const uint64_t value, const OperandSize &size) {
  switch (size) {
  case OPERAND_16:
    m_eip.value = (m_eip.value & MASK_16) | value;
    break;
  case OPERAND_32:
    m_eip.value = (m_eip.value & MASK_32) | value;
    break;
  case OPERAND_64:
    m_eip.value = value;
    break;
  }
}

std::string RegisterBank::name_eip(const OperandSize &size) {
  switch (size) {
  case OPERAND_16:
    return m_eip.name16;
  case OPERAND_32:
    return m_eip.name32;
  case OPERAND_64:
    return m_eip.name64;
  }
}
