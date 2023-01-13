#include "and.hpp"

template <typename T>
T perform_and(State &state, OperandSize size, T op1, T op2) {
  T res = op1 & op2;
  set_common_arithmetic_flags(state, size, res);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF, 0);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, 0);
  return res;
}

void and24_25(State &state) {
  OperandSize size = state.ins.opcode == 0x24 ? OPERAND_8 : OPERAND_32;
  uint32_t imm =
    state.scanner.next_nbytes(1 << size, state.reg_bank, state.mode);
  uint32_t reg_val = state.reg_bank.load(EAX, size);
  uint32_t res = perform_and<uint32_t>(state, size, reg_val, imm);
  state.reg_bank.set(state.ins.snapshot.reg_transition, EAX, res, size);
  set_snapshot(state, AND_INS, format_immediate(imm),
               state.reg_bank.name(EAX, size));
}

void and20(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_8, AND_INS,
    perform_and<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val))
}

void and21(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_32, AND_INS,
    perform_and<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val))
}

void and22(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_8, AND_INS,
    perform_and<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val))
}

void and23(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_32, AND_INS,
    perform_and<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val))
}
