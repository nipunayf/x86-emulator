#include "modrm.hpp"
#include "sib.hpp"
#include <string>

uint32_t register_direct(const uint8_t &reg, RegisterBank &reg_bank) {
  return reg_bank.load32(reg);
}

uint32_t register_indirect(const uint8_t &reg, Scanner &scanner,
                           RegisterBank &reg_bank, Memory &memory) {
  uint32_t memory_addr;
  if (reg == ESP) {
    uint8_t sib = scanner.next_byte();
    memory_addr = process_sib(sib, reg_bank);
  } else if (reg == EBP) {
    uint32_t displacement = scanner.next_four_bytes();
    memory_addr = displacement;
  } else {
    memory_addr = reg_bank.load32(reg);
  }
  return memory.read(memory_addr);
}

uint32_t indirect_one_byte_displacement(const uint8_t &reg, Scanner &scanner,
                                        RegisterBank &reg_bank,
                                        Memory &memory) {
  uint32_t memory_addr;
  uint8_t displacement;
  if (reg == ESP) {
    uint8_t sib = scanner.next_byte();
    displacement = scanner.next_byte();
    memory_addr = process_sib(sib, reg_bank) + displacement;
  } else {
    displacement = scanner.next_byte();
    memory_addr = reg_bank.load32(reg) + displacement;
  }
  return memory.read(memory_addr);
}

uint32_t indirect_four_byte_displacement(const uint8_t &reg, Scanner &scanner,
                                         RegisterBank &reg_bank,
                                         Memory &memory) {
  uint32_t memory_addr, displacement;
  if (reg == ESP) {
    uint8_t sib = scanner.next_byte();
    displacement = scanner.next_four_bytes();
    memory_addr = process_sib(sib, reg_bank) + displacement;
  } else {
    displacement = scanner.next_four_bytes();
    memory_addr = reg_bank.load32(reg) + displacement;
  }
  return memory.read(memory_addr);
}

void process_modmr(const uint8_t &byte, Scanner &scanner,
                   RegisterBank &reg_bank, Memory &memory, uint32_t &operand_rm,
                   uint32_t &operand_reg) {
  const uint8_t mode = byte >> 6;
  const uint8_t rm = byte & 0x07;
  const uint8_t reg = (byte >> 3) & 0x07;
  switch (mode) {
  case REGISTER_INDIRECT:
    operand_rm = register_indirect(rm, scanner, reg_bank, memory);
    break;
  case ONE_BYTE_DISPLACEMENT:
    operand_rm = indirect_one_byte_displacement(rm, scanner, reg_bank, memory);
    break;
  case FOUR_BYTE_DISPLACEMENT:
    indirect_four_byte_displacement(rm, scanner, reg_bank, memory);
    break;
  case REGISTER_DIRECT:
    operand_rm = register_direct(rm, reg_bank);
    break;
  }
  operand_reg = register_direct(reg, reg_bank);
}
