#ifndef OPCODE_INC_H
#define OPCODE_INC_H

#include "../handler.hpp"

#define INC_INS "inc"

void inc4x(State &state);

template <typename T> T perform_inc(State &state, OperandSize op_size, T op) {
  T res = op + 1;
  set_common_arithmetic_flags(state, op_size, res);

  // Set overflow flag (OF)
  // When the msb of the operand changes in the result
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF,
                          read_msb(op_size, op) != read_msb(op_size, res));

  // Set auxiliary carry flag (AF)
  // When the lower nibble of the operand generates a carry
  // Adding 1111 + 1 generates a carry from the lower nibble
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, AF,
                          (op & (T)15) == 15);

  return res;
}

#endif
