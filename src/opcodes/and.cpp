#include "and.hpp"

template <typename T>
T perform_and(State &state, OperandSize size, T op1, T op2) {
  T res = op1 & op2;
  set_common_logical_flags(state, size, res);
  return res;
}

void and24(State &state) {
  IMM_EAX_OPCODE(OPERAND_8, uint8_t, AND_INS,
                 perform_and<uint32_t>(state, OPERAND_8, reg_val, imm))
}

void and25(State &state) {
  IMM_EAX_OPCODE(OPERAND_32, uint32_t, AND_INS,
                 perform_and<uint32_t>(state, OPERAND_32, reg_val, imm))
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
