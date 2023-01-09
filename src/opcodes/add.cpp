#include "add.hpp"

int32_t perform_add(RegisterBank &reg_bank, OperandSize op_size, int32_t op1,
                    int32_t op2) {
  int32_t result = op1 + op2;
  set_common_arithmetic_flags(reg_bank, op_size, op1, op2, result);
  return result;
}

void add03(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  int32_t output = perform_add(state.reg_bank, OPERAND_32, (int32_t)rm_args.val,
                               (int32_t)reg_args.val);
  set_value(state, reg_args, output);

  set_snapshot(state, "add", reg_args.val, output, reg_args.notation,
               rm_args.notation);
}

void add05(State &state) {
  auto reg = (int32_t)state.reg_bank.load32(EAX);
  auto displace = (int32_t)state.scanner.next_nbytes(4);

  int32_t output = perform_add(state.reg_bank, OPERAND_32, reg, displace);
  state.reg_bank.set32(EAX, output);

  set_snapshot(state, "add", reg, output, format_immediate(displace),
               state.reg_bank.name32(EAX));
}
