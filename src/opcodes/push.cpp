#include "push.hpp"

void perform_push(State &state, uint32_t val, std::string notation) {
  uint32_t sp = state.reg_bank.load32(ESP);
  state.memory.store32(state.ins.snapshot.mem_transition, sp, val);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, ESP, sp - 4);
  set_snapshot(state, PUSH_INS, notation);
}

void push5x(State &state) {
  Register32 reg = (Register32)(state.ins.opcode - 0x50);
  perform_push(state, state.reg_bank.load32(reg), state.reg_bank.name32(reg));
}

void push6A(State &state) {
  uint16_t imm = state.scanner.next_nbytes(2, state.reg_bank, state.mode);
  perform_push(state, imm, format_immediate(imm));
}

void push68(State &state) {
  uint32_t imm = state.scanner.next_nbytes(4, state.reg_bank, state.mode);
  perform_push(state, imm, format_immediate(imm));
}

void push_segement_register(State &state, RegisterSeg reg) {
  uint16_t val = state.reg_bank.load_seg(reg);
  perform_push(state, val, state.reg_bank.name_seg(reg));
}

void push0E(State &state) { push_segement_register(state, CS); }

void push16(State &state) { push_segement_register(state, SS); }

void push1E(State &state) { push_segement_register(state, DS); }

void push06(State &state) { push_segement_register(state, ES); }

void push0FA0(State &state) { push_segement_register(state, FS); }

void push0FA8(State &state) { push_segement_register(state, GS); }
