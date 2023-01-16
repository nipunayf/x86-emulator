#include "xchg.hpp"
#include "../modrm.hpp"

void xchg9x(State &state) {
  Register32 reg = (Register32)(state.ins.opcode - 0x90);
  uint32_t temp = state.reg_bank.load32(EAX);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, EAX,
                       state.reg_bank.load32(reg));
  state.reg_bank.set32(state.ins.snapshot.reg_transition, reg, temp);
  set_snapshot(state, XCHG_INS, state.reg_bank.name32(reg),
               state.reg_bank.name32(EAX));
}

void xchg86_87(State &state) {
  OperandSize size = state.ins.opcode == 0x86 ? OPERAND_8 : OPERAND_32;
  ModRMAttribute rm_args{size}, reg_args{size};
  process_modrm(state, rm_args, reg_args);
  set_value(state, reg_args, rm_args.val);
  set_value(state, rm_args, reg_args.val);
  set_snapshot(state, XCHG_INS, rm_args.notation, reg_args.notation);
}
