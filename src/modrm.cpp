#include "modrm.hpp"
#include "sib.hpp"
#include <iostream>
#include <string>

#define SET_REGISTER_NAME(reg_name)                                            \
  if (set_name)                                                                \
    args.name = reg_name;

uint32_t register_direct(RegisterBank &reg_bank, const uint8_t &reg,
                         ModRMAttribute &args, const bool set_name = false) {
  args.addr = reg;
  switch (args.type) {
  case OPERAND_8:
    SET_REGISTER_NAME(reg_bank.name8(reg))
    return reg_bank.load8(reg);
  case OPERAND_16:
    SET_REGISTER_NAME(reg_bank.name16(reg))
    return reg_bank.load16(reg);
  case OPERAND_32:
    SET_REGISTER_NAME(reg_bank.name32(reg))
    return reg_bank.load32(reg);
  case OPERAND_64:
    SET_REGISTER_NAME(reg_bank.name64(reg))
    return reg_bank.load64(reg);
  }
}

uint32_t register_indirect(State &state, const uint8_t &reg,
                           ModRMAttribute args) {
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    args.addr = process_sib(sib, state.reg_bank);
  } else if (reg == EBP) {
    uint32_t displacement = state.scanner.next_nbytes(4);
    args.addr = displacement;
  } else {
    args.addr = register_direct(state.reg_bank, reg, args);
  }
  // TODO: Format the operand name
  args.name = format_displacement(args.addr);
  return state.memory.read(args.addr);
}

uint32_t indirect_one_byte_displacement(State &state, const uint8_t &reg,
                                        ModRMAttribute args) {
  uint8_t displacement;
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    displacement = state.scanner.next_byte();
    args.addr = process_sib(sib, state.reg_bank) + displacement;
  } else {
    displacement = state.scanner.next_byte();
    args.addr = register_direct(state.reg_bank, reg, args) + displacement;
  }
  // TODO: Format the operand name
  args.name = format_displacement(args.addr);
  return state.memory.read(args.addr);
}

uint32_t indirect_four_byte_displacement(State &state, const uint8_t &reg,
                                         ModRMAttribute args) {
  uint32_t displacement;
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    displacement = state.scanner.next_nbytes(4);
    args.addr = process_sib(sib, state.reg_bank) + displacement;
  } else {
    displacement = state.scanner.next_nbytes(4);
    args.addr = register_direct(state.reg_bank, reg, args) + displacement;
  }
  // TODO: Format the operand name
  args.name = format_displacement(args.addr);
  return state.memory.read(args.addr);
}

void process_modrm(State &state, ModRMAttribute &rm_args,
                   ModRMAttribute &reg_args, bool has_extension) {
  const uint8_t byte = state.scanner.next_byte();
  const auto mode = static_cast<const AddressingMode>(byte >> 6);
  const uint8_t rm = byte & 0x07;
  const uint8_t reg = (byte >> 3) & 0x07;

  switch (mode) {
  case REGISTER_INDIRECT:
    rm_args.val = register_indirect(state, rm, rm_args);
    break;
  case ONE_BYTE_DISPLACEMENT:
    rm_args.val = indirect_one_byte_displacement(state, rm, rm_args);
    break;
  case FOUR_BYTE_DISPLACEMENT:
    rm_args.val = indirect_four_byte_displacement(state, rm, rm_args);
    break;
  case REGISTER_DIRECT:
    rm_args.is_reg = true;
    rm_args.val = register_direct(state.reg_bank, rm, rm_args, true);
    break;
  }
  reg_args.val =
    has_extension ? reg : register_direct(state.reg_bank, reg, reg_args, true);
}

void set_value(State &state, ModRMAttribute &args, uint32_t value) {
  if (args.is_reg) {
    switch (args.type) {
    case OPERAND_8:
      state.reg_bank.set8(args.addr, value);
    case OPERAND_16:
      state.reg_bank.set16(args.addr, value);
    case OPERAND_32:
      state.reg_bank.set32(args.addr, value);
    case OPERAND_64:
      state.reg_bank.set64(args.addr, value);
    }
  } else {
    state.memory.store(args.addr, value);
  }
}
