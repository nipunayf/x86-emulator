#include "xor.hpp"

void xor34(State &state) {
  IMM_EAX_OPCODE(OPERAND_8, uint8_t, XOR_INS,
                 perform_xor<uint32_t>(state, OPERAND_8, reg_val, imm))
}

void xor35(State &state) {
  IMM_EAX_OPCODE(OPERAND_32, uint32_t, XOR_INS,
                 perform_xor<uint32_t>(state, OPERAND_32, reg_val, imm))
}

void xor30(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_8, XOR_INS,
    perform_xor<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val))
}

void xor31(State &state) {
  MODRM_DEST_OPCODE(
    OPERAND_32, XOR_INS,
    perform_xor<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val))
}

void xor32(State &state) {
  MODRM_SRC_OPCODE(
    OPERAND_8, XOR_INS,
    perform_xor<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val))
}

void xor33(State &state) {
  MODRM_SRC_OPCODE(
    OPERAND_32, XOR_INS,
    perform_xor<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val))
}
