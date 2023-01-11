#ifndef OPCODE_ADD_H
#define OPCODE_ADD_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define ADD_INS "add"

void add00(State &state);
void add01(State &state);
void add02(State &state);
void add03(State &state);
void add04(State &state);
void add05(State &state);

template <typename T>
T perform_add(State &state, OperandSize op_size, T op1, T op2) {
  T res = op1 + op2;
  set_common_arithmetic_flags(state, op_size, op1, op2, res);

  uint8_t op1_msb = read_msb(op_size, op1);
  uint8_t op2_msb = read_msb(op_size, op2);
  uint8_t res_msb = read_msb(op_size, res);

  // Set overflow flag (OF)
  // In signed integers, when two positive integers or two negative integer
  // operands produce a result with a complemented msb
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF,
                          op1_msb == op2_msb && res_msb != op1_msb);

  // Set carry flag (CF)
  // In unsigned integers, when the generated result cannot be held by the
  // destination register
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF,
                          (op1_msb == 1 && op2_msb == 1) ||
                            ((op1_msb == 1 || op2_msb == 1) && res_msb == 0));

  // Set auxiliary carry flag (AF)
  // When the lower nibble of the both operands generates a carry
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, AF,
                          (op1 & (T)15) + (op2 & (T)15) > 15);

  return res;
}

#endif
