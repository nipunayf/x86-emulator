#ifndef OPCODE_DEC_H
#define OPCODE_DEC_H

#include "../handler.hpp"

#define DEC_INS "dec"

void dec4x(State &state);

template <typename T> T perform_dec(State &state, OperandSize op_size, T op) {
  T res = op - 1;
  set_common_arithmetic_flags(state, op_size, res);

  // Set overflow flag (OF)
  // When the msb of the operand changes in the result
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF,
                          read_msb(op_size, op) != read_msb(op_size, res));

  // Set auxiliary carry flag (AF)
  // When a borrow is fed to the lower nibble
  // Subtracting 0000 - 1 generates a borrow for the lower nibble
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, AF,
                          (op & (T)15) == 0);

  return res;
}

#endif
