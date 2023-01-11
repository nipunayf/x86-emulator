#include "add.hpp"

void add00(State &state) {
  ModRMAttribute rm_args{OPERAND_8}, reg_args{OPERAND_8};
  process_modrm(state, rm_args, reg_args);

  auto output = perform_add<int8_t>(state, OPERAND_8, (int8_t)rm_args.val,
                                    (int8_t)reg_args.val);
  set_value(state, rm_args, output);

  set_snapshot(state, "add", rm_args.notation, reg_args.notation);
}

void add01(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  auto output = perform_add<int32_t>(state, OPERAND_32, (int32_t)rm_args.val,
                                     (int32_t)reg_args.val);
  set_value(state, rm_args, output);

  set_snapshot(state, "add", rm_args.notation, reg_args.notation);
}

void add02(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  auto output = perform_add<int8_t>(state, OPERAND_32, (int8_t)reg_args.val,
                                    (int8_t)rm_args.val);
  set_value(state, reg_args, output);

  set_snapshot(state, "add", reg_args.notation, rm_args.notation);
}

void add03(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  auto output = perform_add<int32_t>(state, OPERAND_32, (int32_t)rm_args.val,
                                     (int32_t)reg_args.val);
  set_value(state, reg_args, output);

  set_snapshot(state, "add", reg_args.notation, rm_args.notation);
}

void add04(State &state) {
  auto reg = (int32_t)state.reg_bank.load8(AL);
  auto displace = (int32_t)state.scanner.next_nbytes(1);

  auto output = perform_add<int8_t>(state, OPERAND_8, reg, displace);
  state.reg_bank.set8(state.ins.snapshot.reg_transition, AL, output);

  set_snapshot(state, "add", format_immediate(displace),
               state.reg_bank.name32(AL));
}

void add05(State &state) {
  auto reg = (int32_t)state.reg_bank.load32(EAX);
  auto displace = (int32_t)state.scanner.next_nbytes(4);

  auto output = perform_add<int32_t>(state, OPERAND_32, reg, displace);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, EAX, output);

  set_snapshot(state, "add", format_immediate(displace),
               state.reg_bank.name32(EAX));
}
