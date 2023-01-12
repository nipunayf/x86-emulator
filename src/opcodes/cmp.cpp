#include "cmp.hpp"
#include "sub.hpp"

void cmp3C(State &state) {
  uint8_t imm = state.scanner.next_byte();
  perform_sub<uint8_t>(state, OPERAND_8, state.reg_bank.load8(AL), imm);
  set_snapshot(state, CMP_INS, format_immediate(imm), state.reg_bank.name8(AL));
}

void cmp3D(State &state) {
  uint32_t imm = state.scanner.next_nbytes(4);
  perform_sub<uint32_t>(state, OPERAND_8, state.reg_bank.load32(EAX), imm);
  set_snapshot(state, CMP_INS, format_immediate(imm),
               state.reg_bank.name32(EAX));
}

void cmp38(State &state) {
  ModRMAttribute rm_args{OPERAND_8}, reg_args{OPERAND_8};
  process_modrm(state, rm_args, reg_args);
  perform_sub<uint8_t>(state, OPERAND_8, rm_args.val, reg_args.val);
  set_snapshot(state, CMP_INS, rm_args.notation, reg_args.notation);
}

void cmp39(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);
  perform_sub<uint32_t>(state, OPERAND_32, rm_args.val, reg_args.val);
  set_snapshot(state, CMP_INS, rm_args.notation, reg_args.notation);
}

void cmp3A(State &state) {
  ModRMAttribute rm_args{OPERAND_8}, reg_args{OPERAND_8};
  process_modrm(state, rm_args, reg_args);
  perform_sub<uint8_t>(state, OPERAND_8, reg_args.val, rm_args.val);
  set_snapshot(state, CMP_INS, reg_args.notation, rm_args.notation);
}

void cmp3B(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);
  perform_sub<uint32_t>(state, OPERAND_32, reg_args.val, rm_args.val);
  set_snapshot(state, CMP_INS, reg_args.notation, rm_args.notation);
}
