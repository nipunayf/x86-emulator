#include "nop.hpp"

void nop90(State &state) { set_snapshot(state, NOP_INS); }

void nop0F1F(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);

  set_snapshot(state, NOP_INS, rm_args.notation);
}
