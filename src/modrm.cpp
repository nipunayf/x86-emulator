#include "modrm.hpp"
#include "sib.hpp"
#include <iostream>
#include <string>

void indirect_16bit_addressing(RegisterBank &reg_bank, uint32_t index,
                               ModRMAttribute &args) {
  switch (index) {
  case 0:
    args.mem_addr = reg_bank.load16(BX) + reg_bank.load16(SI);
    args.notation = format_base_index(reg_bank.name16(BX), reg_bank.name16(SI));
    break;
  case 1:
    args.mem_addr = reg_bank.load16(BX) + reg_bank.load16(DI);
    args.notation = format_base_index(reg_bank.name16(BX), reg_bank.name16(DI));
    break;
  case 2:
    args.mem_addr = reg_bank.load16(BP) + reg_bank.load16(SI);
    args.notation = format_base_index(reg_bank.name16(BP), reg_bank.name16(SI));
    break;
  case 3:
    args.mem_addr = reg_bank.load16(BP) + reg_bank.load16(DI);
    args.notation = format_base_index(reg_bank.name16(BP), reg_bank.name16(DI));
    break;
  case 4:
    args.mem_addr = reg_bank.load16(SI);
    args.notation = format_indirect_register(reg_bank.name16(SI));
    break;
  case 5:
    args.mem_addr = reg_bank.load16(DI);
    args.notation = format_indirect_register(reg_bank.name16(DI));
    break;
  case 6:
    args.mem_addr = reg_bank.load16(BP);
    args.notation = format_indirect_register(reg_bank.name16(BP));
    break;
  case 7:
    args.mem_addr = reg_bank.load16(BX);
    args.notation = format_indirect_register(reg_bank.name16(BX));
    break;
  }
}

void indirect_32bit_addressing(State &state, uint32_t reg,
                               ModRMAttribute &args) {
  if (reg == ESP) {
    uint8_t sib = state.scanner.next_byte();
    args.mem_addr = process_sib(sib, state.reg_bank, args.notation);
  } else {
    args.mem_addr = state.reg_bank.load(reg, args.type);
    args.notation =
      format_indirect_register(state.reg_bank.name(reg, args.type));
  }
}

uint32_t register_direct(RegisterBank &reg_bank, const uint8_t &reg,
                         ModRMAttribute &args) {
  args.reg = reg;
  args.notation = reg_bank.name(reg, args.type);
  return reg_bank.load(reg, args.type);
}

uint32_t register_indirect(State &state, const uint8_t &reg,
                           ModRMAttribute args) {
  if (args.type == OPERAND_16) {
    if (reg == 6) {
      uint32_t displacement = state.scanner.next_nbytes(2);
      args.mem_addr = displacement;
      args.notation = format_memory_address(displacement);
    } else {
      indirect_16bit_addressing(state.reg_bank, reg, args);
    }
  } else {
    if (reg == EBP) {
      uint32_t displacement = state.scanner.next_nbytes(4);
      args.mem_addr = displacement;
      args.notation = format_memory_address(displacement);
    } else {
      indirect_32bit_addressing(state, reg, args);
    }
  }
  return state.memory.read(args.mem_addr);
}

uint32_t indirect_nbyte_displacement(State &state, const uint8_t &mode,
                                     const uint8_t &reg, ModRMAttribute args) {
  uint32_t displacement = 0;
  if (args.type == OPERAND_16) {
    indirect_16bit_addressing(state.reg_bank, reg, args);
    displacement = state.scanner.next_nbytes(mode);
  } else {
    indirect_32bit_addressing(state, reg, args);
    displacement = state.scanner.next_nbytes(mode == 1 ? 1 : 4);
  }
  args.notation =
    format_indirect_with_displacement(args.notation, displacement);
  return state.memory.read(args.mem_addr + displacement);
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
  case TWO_OR_FOUR_BYTE_DISPLACEMENT:
    rm_args.val = indirect_nbyte_displacement(state, mode, rm, rm_args);
    break;
  case REGISTER_DIRECT:
    rm_args.val = register_direct(state.reg_bank, rm, rm_args);
    break;
  }
  reg_args.val = register_direct(state.reg_bank, reg, reg_args);
}

void set_value(State &state, ModRMAttribute &args, uint32_t value) {
  if (args.reg != REG_UNSET)
    state.reg_bank.set(args.reg, value, args.type);
  else
    state.memory.store(args.mem_addr, value);
}
