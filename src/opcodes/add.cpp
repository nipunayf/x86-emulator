#include "add.hpp"

int32_t perform_add(State &state, OperandSize op_size, int32_t op1,
                    int32_t op2) {
  int32_t res = op1 + op2;
  set_common_arithmetic_flags(state, op_size, op1, op2, res);

  // Set overflow flag (OF)
  // When two positive integers or two negative integer operands produce a
  // result with a complemented msb
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF,
                          read_msb(op_size, op1) == read_msb(op_size, op2) &&
                            read_msb(op_size, res) != read_msb(op_size, op1));
  return res;
}

void add03(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  int32_t output =
    perform_add(state, OPERAND_32, (int32_t)rm_args.val, (int32_t)reg_args.val);
  set_value(state, reg_args, output);

  set_snapshot(state, "add", reg_args.notation, rm_args.notation);
}

void add05(State &state) {
  auto reg = (int32_t)state.reg_bank.load32(EAX);
  auto displace = (int32_t)state.scanner.next_nbytes(4);

  int32_t output = perform_add(state, OPERAND_32, reg, displace);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, EAX, output);

  set_snapshot(state, "add", format_immediate(displace),
               state.reg_bank.name32(EAX));
}
