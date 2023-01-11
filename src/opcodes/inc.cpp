#include "inc.hpp"

void inc4x(State &state) {
  auto reg = (Register32)(state.ins.opcode - 0x40);

  auto res = perform_inc<int32_t>(state, OPERAND_32,
                                  (int32_t)state.reg_bank.load32(reg));
  state.reg_bank.set32(state.ins.snapshot.reg_transition, reg, res);

  set_snapshot(state, INC_INS, state.reg_bank.name32(reg));
}
