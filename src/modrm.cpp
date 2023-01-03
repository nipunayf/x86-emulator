#include "modrm.hpp"
#include "sib.hpp"
#include <string>

uint32_t register_direct(const uint8_t &reg, RegisterBank &reg_bank) {
  return reg_bank.load(reg);
}

uint32_t register_indirect(const uint8_t &reg, RegisterBank &reg_bank,
                          Memory &memory) {
  uint32_t memory_addr;
  if (reg == ESP) {
    // TODO: Replace retrieving next byte of the input
    uint8_t sib = 0xEF;
    memory_addr = process_sib(sib, reg_bank);
  } else if (reg == EBP) {
    // TODO&CHECK: Replace retrieving next four bytes of the input
    uint32_t displacement = 0xEFEFEFEF;
    memory_addr = displacement;
  } else {
    memory_addr = reg_bank.load(reg);
  }
  return memory.read(memory_addr);
}

uint32_t indirect_one_byte_displacement(const uint8_t &reg, RegisterBank &reg_bank,
                                     Memory &memory) {
  uint32_t memory_addr;
  if (reg == ESP) {
    // TODO: Replace with retrieving the next byte of the input
    uint8_t sib = 0xEF;
    // CHECK
    uint8_t displacement = 0xEF;
    memory_addr = process_sib(sib, reg_bank) + displacement;
  } else {
    // TODO: Replace with retrieving the next byte of the input
    uint8_t displacement = 0xEF;
    memory_addr = reg_bank.load(reg) + displacement;
  }
  return memory.read(memory_addr);
}

uint32_t indirect_four_byte_displacement(const uint8_t &reg, RegisterBank &reg_bank,
                                      Memory &memory) {
  uint32_t memory_addr;
  if (reg == ESP) {
    // TODO: Replace retrieving next four bytes of the input
    uint8_t sib = 0xEF;
    // CHECK
    uint32_t displacement = 0xEFEFEFEF;
    memory_addr = process_sib(sib, reg_bank) + displacement;
  } else {
    // TODO: Replace retrieving the next four bytes of the input
    uint32_t displacement = 0xEFEFEFEF;
    memory_addr = reg_bank.load(reg) + displacement;
  }
  return memory.read(memory_addr);
}

void process_modmr(const uint8_t &byte, RegisterBank &reg_bank, Memory &memory,
                  uint32_t &operand_rm, uint32_t &operand_reg) {
  const uint8_t mode = byte >> 6;
  const uint8_t rm = byte & 0x07;
  const uint8_t reg = (byte >> 3) & 0x07;
  switch (mode) {
  case REGISTER_INDIRECT:
    operand_rm = register_indirect(rm, reg_bank, memory);
    break;
  case ONE_BYTE_DISPLACEMENT:
    operand_rm = indirect_one_byte_displacement(rm, reg_bank, memory);
    break;
  case FOUR_BYTE_DISPLACEMENT:
    indirect_four_byte_displacement(rm, reg_bank, memory);
    break;
  case REGISTER_DIRECT:
    operand_rm = register_direct(rm, reg_bank);
    break;
  }
  operand_reg = register_direct(reg, reg_bank);
}
