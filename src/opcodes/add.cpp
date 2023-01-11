#include "add.hpp"

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
  uint8_t op1_lower_nibble = op1 & (T)15;
  uint8_t op2_lower_nibble = op2 & (T)15;
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, AF,
                          op1_lower_nibble + op2_lower_nibble > 15);

  return res;
}

void add03(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  auto output = perform_add<int32_t>(state, OPERAND_32, (int32_t)rm_args.val,
                                     (int32_t)reg_args.val);
  set_value(state, reg_args, output);

  set_snapshot(state, "add", reg_args.notation, rm_args.notation);
}

void add05(State &state) {
  auto reg = (int32_t)state.reg_bank.load32(EAX);
  auto displace = (int32_t)state.scanner.next_nbytes(4);

  auto output = perform_add<int32_t>(state, OPERAND_32, reg, displace);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, EAX, output);

  set_snapshot(state, "add", format_immediate(displace),
               state.reg_bank.name32(EAX));
}
