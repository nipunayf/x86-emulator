#ifndef OPCODE_SUB_H
#define OPCODE_SUB_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define SUB_INS "sub"

void sub28(State &state);
void sub29(State &state);
void sub2A(State &state);
void sub2B(State &state);
void sub2C(State &state);
void sub2D(State &state);

template <typename T>
T perform_sub(State &state, OperandSize op_size, T op1, T op2) {
  T res = op1 - op2;
  set_common_arithmetic_flags(state, op_size, op1, op2, res);

  uint8_t op1_msb = read_msb(op_size, op1);
  uint8_t op2_msb = read_msb(op_size, op2);
  uint8_t res_msb = read_msb(op_size, res);

  // Set overflow flag (OF)
  // In signed integers, the second operand takes the sign of the first operand
  // when subtracting. Hence, we can check the same case as add with
  // complemented conditions
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF,
                          op1_msb != op2_msb && res_msb != op1_msb);

  // Set carry flag (CF)
  // In unsigned integers, when the second operand is higher, a borrow is needed
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, op1 < op2);

  // Set auxiliary carry flag (AF)
  // When the lower nibble requires a borrow has the same logic as CF
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, AF,
                          (op1 & (T)15) < (op2 & (T)15));

  return res;
}

#endif
