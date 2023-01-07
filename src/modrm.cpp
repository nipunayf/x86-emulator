#include "modrm.hpp"
#include "sib.hpp"
#include <iostream>
#include <string>

uint32_t register_direct(RegisterBank &reg_bank, const uint8_t &reg,
                         RegisterType reg_type, std::string &reg_name) {
  switch (reg_type) {
    // TODO: Uncomment after implementation of register 8
    //  case REGISTER_8:
    //    reg_name = reg_bank.name8(reg);
    //    return reg_bank.load8(reg);
  case REGISTER_16:
    reg_name = reg_bank.name16(reg);
    return reg_bank.load16(reg);
  case REGISTER_32:
    reg_name = reg_bank.name32(reg);
    return reg_bank.load32(reg);
  case REGISTER_64:
    reg_name = reg_bank.name64(reg);
    return reg_bank.load64(reg);
  }
}

uint32_t register_direct(RegisterBank &reg_bank, const uint8_t &reg,
                         RegisterType reg_type) {
  switch (reg_type) {
    // TODO: Uncomment after implementation of register 8
    //  case REGISTER_8:
    //    return reg_bank.load8(reg);
  case REGISTER_16:
    return reg_bank.load16(reg);
  case REGISTER_32:
    return reg_bank.load32(reg);
  case REGISTER_64:
    return reg_bank.load64(reg);
  }
}

uint32_t register_indirect(State &state, const uint8_t &reg,
                           RegisterType reg_type, std::string &reg_name,
                           uint32_t &memory_addr) {
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    memory_addr = process_sib(sib, state.reg_bank);
  } else if (reg == EBP) {
    uint32_t displacement = state.scanner.next_nbytes(4);
    memory_addr = displacement;
  } else {
    memory_addr = register_direct(state.reg_bank, reg, reg_type);
  }
  //TODO: Format the operand name
  reg_name = format_displacement(memory_addr);
  return state.memory.read(memory_addr);
}

uint32_t indirect_one_byte_displacement(State &state, const uint8_t &reg,
                                        RegisterType reg_type,
                                        std::string &reg_name,
                                        uint32_t &memory_addr) {
  uint8_t displacement;
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    displacement = state.scanner.next_byte();
    memory_addr = process_sib(sib, state.reg_bank) + displacement;
  } else {
    displacement = state.scanner.next_byte();
    memory_addr = register_direct(state.reg_bank, reg, reg_type) + displacement;
  }
  //TODO: Format the operand name
  reg_name = format_displacement(memory_addr);
  return state.memory.read(memory_addr);
}

uint32_t indirect_four_byte_displacement(State &state, const uint8_t &reg,
                                         RegisterType reg_type,
                                         std::string &reg_name,
                                         uint32_t &memory_addr) {
  uint32_t displacement;
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    displacement = state.scanner.next_nbytes(4);
    memory_addr = process_sib(sib, state.reg_bank) + displacement;
  } else {
    displacement = state.scanner.next_nbytes(4);
    memory_addr = register_direct(state.reg_bank, reg, reg_type) + displacement;
  }
  //TODO: Format the operand name
  reg_name = format_displacement(memory_addr);
  return state.memory.read(memory_addr);
}

void process_modrm(State &state, ModRMAttribute &args) {
  const uint8_t byte = state.scanner.next_byte();
  const auto mode = static_cast<const AddressingMode>(byte >> 6);
  const uint8_t rm = byte & 0x07;
  const uint8_t reg = (byte >> 3) & 0x07;

  switch (mode) {
  case REGISTER_INDIRECT:
    args.rm_val =
      register_indirect(state, rm, args.rm_type, args.rm_name, args.rm_addr);
    break;
  case ONE_BYTE_DISPLACEMENT:
    args.rm_val = indirect_one_byte_displacement(state, rm, args.rm_type,
                                                 args.rm_name, args.rm_addr);
    break;
  case FOUR_BYTE_DISPLACEMENT:
    args.rm_val = indirect_four_byte_displacement(state, rm, args.rm_type,
                                                  args.rm_name, args.rm_addr);
    break;
  case REGISTER_DIRECT:
    args.is_reg = true;
    args.rm_addr = rm;
    args.rm_val =
      register_direct(state.reg_bank, rm, args.rm_type, args.rm_name);
    break;
  }
  args.reg_addr = reg;
  args.reg_val =
    register_direct(state.reg_bank, reg, args.reg_type, args.reg_name);
}

void set_value(State &state, RegisterType type, uint32_t addr, uint32_t value,
               bool is_reg) {
  if (is_reg) {
    switch (type) {
    case REGISTER_8:
      state.reg_bank.set8(addr, value);
    case REGISTER_16:
      state.reg_bank.set16(addr, value);
    case REGISTER_32:
      state.reg_bank.set32(addr, value);
    case REGISTER_64:
      state.reg_bank.set64(addr, value);
    }
  } else {
    state.memory.store(addr, value);
  }
}
