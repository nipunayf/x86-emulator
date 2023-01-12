#include "move.hpp"
#include "../modrm.hpp"

void mov88(State &state) {
  MODRM_DEST_OPCODE(state, OPERAND_8, MOV_INS,
                    state.reg_bank.load8(reg_args.reg))
}

void mov89(State &state) {
  MODRM_DEST_OPCODE(state, OPERAND_32, MOV_INS,
                    state.reg_bank.load32(reg_args.reg))
}

void mov8A(State &state) {
  MODRM_SRC_OPCODE(state, OPERAND_8, MOV_INS, rm_args.val)
}

void mov8B(State &state) {
  MODRM_SRC_OPCODE(state, OPERAND_32, MOV_INS, rm_args.val)
}

void mov8C(State &state) {
  // Operation Mode can be changed to 16 bit here from prefixes
  ModRMAttribute rm_args{OPERAND_16}, reg_args{OPERAND_16};
  process_modrm(state, rm_args, reg_args);
  reg_args.notation = state.reg_bank.name_seg(reg_args.reg);
  set_value(state, rm_args, state.reg_bank.load_seg(reg_args.reg));
  set_snapshot(state, MOV_INS, reg_args.notation, rm_args.notation);
}

void mov8E(State &state) {
  // Operation Mode can be changed to 16 bit here from prefixes
  ModRMAttribute rm_args{OPERAND_16}, reg_args{OPERAND_16};
  process_modrm(state, rm_args, reg_args);
  state.reg_bank.set_seg(state.ins.snapshot.reg_transition, reg_args.reg,
                         rm_args.val);
  set_snapshot(state, MOV_INS, rm_args.notation, reg_args.notation);
}

void movA0(State &state) {
  uint32_t offset = state.scanner.next_nbytes(1 << state.mode);
  uint8_t output = state.memory.load8(offset);
  state.reg_bank.set8(state.ins.snapshot.reg_transition, AL, output);
  set_snapshot(state, MOV_INS, format_memory_address(offset),
               state.reg_bank.name8(AL));
}

void movA1(State &state) {
  uint32_t offset = state.scanner.next_nbytes(1 << state.mode);
  uint32_t output = state.memory.load32(offset);
  state.reg_bank.set32(state.ins.snapshot.reg_transition, EAX, output);
  set_snapshot(state, MOV_INS, format_memory_address(offset),
               state.reg_bank.name32(EAX));
}

void movA2(State &state) {
  uint32_t addr = state.scanner.next_nbytes(4);
  uint8_t output = state.reg_bank.load8(AL);
  state.memory.store8(state.ins.snapshot.mem_transition, addr, output);
  set_snapshot(state, MOV_INS, state.reg_bank.name8(AL),
               format_memory_address(addr));
}

void movA3(State &state) {
  uint32_t addr = state.scanner.next_nbytes(1 << state.mode);
  uint32_t output = state.reg_bank.load32(EAX);
  state.memory.store32(state.ins.snapshot.mem_transition, addr, output);
  set_snapshot(state, MOV_INS, format_memory_address(addr),
               state.reg_bank.name32(EAX));
}

void movBx(State &state) {
  OperandSize size = state.ins.opcode > 0xB7 ? OPERAND_32 : OPERAND_8;
  uint8_t reg = state.ins.opcode - (state.ins.opcode > 0xB7 ? 0xB8 : 0xB0);
  uint32_t imm = state.scanner.next_nbytes(1 << size);
  state.reg_bank.set(state.ins.snapshot.reg_transition, reg, imm, size);
  set_snapshot(state, MOV_INS, format_immediate(imm),
               state.reg_bank.name(reg, size));
}

void movCx(State &state) {
  OperandSize size = state.ins.opcode == 0xC6 ? OPERAND_8 : OPERAND_32;
  ModRMAttribute rm_args{size}, reg_args{size};
  process_modrm(state, rm_args, reg_args);
  uint32_t imm = state.scanner.next_nbytes((1 << size));
  set_value(state, rm_args, imm);
  set_snapshot(state, MOV_INS, format_immediate(imm), rm_args.notation);
}