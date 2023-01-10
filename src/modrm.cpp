#include "modrm.hpp"
#include "sib.hpp"
#include <iostream>
#include <string>

uint32_t register_direct(RegisterBank &reg_bank, const uint8_t &reg,
                         ModRMAttribute &args) {
  args.reg = reg;
  args.notation = reg_bank.name(reg, args.type);
  return reg_bank.load(reg, args.type);
}

uint32_t register_indirect(State &state, const uint8_t &reg,
                           ModRMAttribute args) {
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    args.mem_addr = process_sib(sib, state.reg_bank, args.notation);
  } else if (reg == EBP) {
    uint32_t displacement = state.scanner.next_nbytes(4);
    args.mem_addr = displacement;
    args.notation = format_memory_address(displacement);
  } else {
    args.mem_addr = state.reg_bank.load(reg, args.type);
    args.notation =
      format_indirect_register(state.reg_bank.name(reg, args.type));
  }
  return state.memory.read(args.mem_addr);
}

uint32_t indirect_one_byte_displacement(State &state, const uint8_t &reg,
                                        ModRMAttribute args) {
  uint8_t displacement;
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    displacement = state.scanner.next_byte();
    args.mem_addr =
      process_sib(sib, state.reg_bank, args.notation, displacement);
  } else {
    displacement = state.scanner.next_byte();
    args.mem_addr = state.reg_bank.load(reg, args.type) + displacement;
    args.notation = format_indirect_with_displacement(
      state.reg_bank.name(reg, args.type), displacement);
  }
  return state.memory.read(args.mem_addr);
}

uint32_t indirect_four_byte_displacement(State &state, const uint8_t &reg,
                                         ModRMAttribute args) {
  uint32_t displacement;
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    displacement = state.scanner.next_nbytes(4);
    args.mem_addr =
      process_sib(sib, state.reg_bank, args.notation, displacement);
  } else {
    displacement = state.scanner.next_nbytes(4);
    args.mem_addr = state.reg_bank.load(reg, args.type) + displacement;
    args.notation = format_indirect_with_displacement(
      state.reg_bank.name(reg, args.type), displacement);
  }
  return state.memory.read(args.mem_addr);
}

void process_modrm(State &state, ModRMAttribute &rm_args,
                   ModRMAttribute &reg_args) {
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
    rm_args.val = register_direct(state.reg_bank, rm, rm_args);
    break;
  }
  reg_args.val = register_direct(state.reg_bank, reg, reg_args);
}

void set_value(State &state, ModRMAttribute &args, uint32_t value) {
  if (args.reg != REG_UNSET)
    state.reg_bank.set(state.args.snapshot.reg_transition, args.reg, value,
                       args.type);
  else
    state.memory.store(state.args.snapshot.mem_transition, args.mem_addr, value);
}
