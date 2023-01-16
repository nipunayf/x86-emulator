#include "cmp.hpp"
#include "sub.hpp"

void cmp3C(State &state) {
  uint8_t imm = state.ins_fetcher.next_byte();
  perform_sub<uint8_t>(state, OPERAND_8, state.reg_bank.load8(AL), imm);
  set_snapshot(state, CMP_INS, state.reg_bank.name8(AL), format_immediate(imm));
}

void cmp3D(State &state) {
  uint32_t imm = state.ins_fetcher.next_nbytes(4);
  perform_sub<uint32_t>(state, OPERAND_8, state.reg_bank.load32(EAX), imm);
  set_snapshot(state, CMP_INS, state.reg_bank.name32(EAX),
               format_immediate(imm));
}

void cmp38(State &state) { MODRM_CMP_SRC(OPERAND_8, uint8_t) }

void cmp39(State &state) { MODRM_CMP_SRC(OPERAND_32, uint32_t) }

void cmp3A(State &state) { MODRM_CMP_DEST(OPERAND_8, uint8_t) }

void cmp3B(State &state) { MODRM_CMP_DEST(OPERAND_32, uint32_t) }
