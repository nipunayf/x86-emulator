#include "test.hpp"

void perform_test(State &state, OperandSize op_size, uint32_t op1,
                  uint32_t op2) {
  uint32_t res = op1 & op2;
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, SF,
                          read_msb(op_size, res));
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF, 0);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, 0);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, ZF, res == 0);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, PF,
                          !__builtin_parity(res & MASK8));
}

void testA8_A9(State &state) {
  OperandSize size = state.ins.opcode == 0xA8 ? OPERAND_8 : OPERAND_32;
  uint32_t imm = state.scanner.next_nbytes(1 << size);
  perform_test(state, size, imm, state.reg_bank.load(EAX, size));
  set_snapshot(state, TEST_INS, format_immediate(imm),
               state.reg_bank.name(EAX, size));
}

void test84_85(State &state) {
  OperandSize size = state.ins.opcode == 0x85 ? OPERAND_8 : OPERAND_32;
  ModRMAttribute rm_args{size}, reg_args{size};
  process_modrm(state, rm_args, reg_args);
  perform_test(state, size, rm_args.val, reg_args.val);
  set_snapshot(state, TEST_INS, rm_args.notation, reg_args.notation);
}
