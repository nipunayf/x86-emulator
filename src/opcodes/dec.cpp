#include "dec.hpp"

void dec4x(State &state) {
  auto reg = (Register32)(state.ins.opcode - 0x48);

  auto res = perform_dec<int32_t>(state, OPERAND_32,
                                  (int32_t)state.reg_bank.load32(reg));
  state.reg_bank.set32(state.ins.snapshot.reg_transition, reg, res);

  set_snapshot(state, DEC_INS, state.reg_bank.name32(reg));
}
