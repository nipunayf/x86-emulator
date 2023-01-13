#include "or.hpp"

template <typename T>
T perform_or(State &state, OperandSize size, T op1, T op2) {
  T res = op1 | op2;
  set_common_arithmetic_flags(state, size, res);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF, 0);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, 0);
  return res;
}

void or0C(State &state) {
  IMM_EAX_OPCODE(OPERAND_8, uint8_t, OR_INS,
                 perform_or<uint8_t>(state, OPERAND_8, reg_val, imm))
}

void or0D(State &state) {
  IMM_EAX_OPCODE(OPERAND_32, uint32_t, OR_INS,
                 perform_or<uint32_t>(state, OPERAND_32, reg_val, imm))
}

void or08(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_8, OR_INS,
    perform_or<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val))
}

void or09(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_32, OR_INS,
    perform_or<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val))
}

void or0A(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_8, OR_INS,
    perform_or<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val))
}

void or0B(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_32, OR_INS,
    perform_or<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val))
}
