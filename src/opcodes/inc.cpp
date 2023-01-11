#include "inc.hpp"

template <typename T>
int32_t perform_inc(State &state, T op, OperandSize op_size) {
  T res = op + 1;

  set_common_arithmetic_flags(state, op_size, op, 1, res);

  return res;
}

void inc4x(State &state) {
  Register32 reg = (Register32)(state.ins.opcode - 0x40);
  uint32_t reg_value = state.reg_bank.load32(reg);
  std::string reg_name = state.reg_bank.name32(reg);

  int32_t res = perform_inc<int32_t>(state, (int32_t)state.reg_bank.load32(reg),
                                     OPERAND_32);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, reg, res);

  set_snapshot(state, "inc", state.reg_bank.name32(reg));
}
