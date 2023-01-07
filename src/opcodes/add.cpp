#include "add.hpp"

void add03(State &state) {
  ModRMAttribute rm_args{REGISTER_32}, reg_args{REGISTER_32};
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

  set_snapshot(state, "add", reg, output, format_displacement(displace),
               state.reg_bank.name32(EAX));
}

void add83(State &state) {
  ModRMAttribute rm_args{REGISTER_32}, reg_args{REGISTER_32};
  process_modrm(state, rm_args, reg_args);
  uint32_t displace = state.scanner.next_nbytes(1);

  uint32_t output = rm_args.val + displace;
  set_value(state, rm_args, output);

  set_snapshot(state, "add", rm_args.val, output, format_displacement(displace),
               rm_args.name);
}
