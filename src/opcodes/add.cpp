#include "add.hpp"

void add03(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  uint32_t output = rm_args.val + reg_args.val;
  set_value(state, reg_args, output);

  set_snapshot(state, "add", reg_args.val, output, reg_args.name, rm_args.name);
}

void add05(State &state) {
  uint32_t reg = state.reg_bank.load32(EAX);
  uint32_t displace = state.scanner.next_nbytes(4);

  uint32_t output = reg + displace;
  state.reg_bank.set32(EAX, output);

  set_snapshot(state, "add", reg, output, format_immediate(displace),
               state.reg_bank.name32(EAX));
}

