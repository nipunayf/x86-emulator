#include "inc.hpp"

void inc4x(State &state) {
  Register32 reg = (Register32)(state.ins.opcode - 0x40);
  uint32_t reg_value = state.reg_bank.load32(reg);
  std::string reg_name = state.reg_bank.name32(reg);

  state.reg_bank.set32(state.ins.snapshot.reg_transition, reg, reg_value + 1);

  set_snapshot(state, "inc", state.reg_bank.name32(reg));
}
