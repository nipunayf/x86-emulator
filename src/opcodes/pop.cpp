#include "pop.hpp"

uint32_t perform_pop(State &state) {
  uint32_t sp = state.reg_bank.load32(ESP);
  uint32_t val = state.memory.load32(sp);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, ESP, sp + 4);
  return val;
}

void pop5x(State &state) {
  auto dest = (Register32)(state.ins.opcode - 0x58);
  uint32_t val = perform_pop(state);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, dest, val);
  set_snapshot(state, "pop", state.reg_bank.name32(dest));
}

void pop_seg_register(State &state, RegisterSeg dest) {
  uint32_t sp = state.reg_bank.load32(ESP);
  uint16_t val = state.memory.load16(sp);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, ESP, sp + 2);
  state.reg_bank.set_seg(state.ins.snapshot.reg_transition, dest, val);
  set_snapshot(state, "pop", state.reg_bank.name_seg(dest));
}

void pop1F(State &state) { pop_seg_register(state, DS); }

void pop07(State &state) { pop_seg_register(state, ES); }

void pop17(State &state) { pop_seg_register(state, SS); }

void pop0FA1(State &state) { pop_seg_register(state, FS); }

void pop0FA9(State &state) { pop_seg_register(state, GS); }
