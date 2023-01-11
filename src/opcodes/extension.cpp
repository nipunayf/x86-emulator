#include "extension.hpp"
#include "add.hpp"
#include "pop.hpp"
#include "push.hpp"
#include <cmath>

uint32_t read_immediate(Scanner &scanner, OperandSize type) {
  return scanner.next_nbytes(pow(2, type));
}

void ext8x(State &state, OperandSize reg_type, OperandSize im_type) {
  ModRMAttribute rm_args{reg_type}, reg_args{im_type};
  process_modrm(state, rm_args, reg_args);
  uint32_t imm = read_immediate(state.scanner, OPERAND_8);
  std::string operation;
  uint32_t output;
  switch (reg_args.reg) {
  case 0:
    operation = "add";
    output = perform_add(state, reg_type, rm_args.val, imm);
    break;
  default:
    print_error_and_exit("Instruction %d / %d not yet implemented",
                         format_hex_string(state.ins.opcode), reg_args.reg);
    break;
  }
  set_value(state, rm_args, output);
  set_snapshot(state, operation, format_immediate(imm), rm_args.notation);
}

void ext80(State &state) { ext8x(state, OPERAND_8, OPERAND_8); }

void ext81(State &state) { ext8x(state, OPERAND_32, OPERAND_32); }

void ext83(State &state) { ext8x(state, OPERAND_32, OPERAND_8); }

void extFF(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);
  uint32_t output;
  switch (reg_args.reg) {
  case 6:
    perform_push(state, rm_args.val, rm_args.notation);
    break;
  default:
    print_error_and_exit("Instruction %s / %d not yet implemented",
                         format_hex_string(state.ins.opcode), reg_args.reg);
    break;
  }
}

void ext8F(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);
  std::string operation;
  uint32_t output;
  switch (reg_args.reg) {
  case 0:
    operation = "pop";
    output = perform_pop(state);
    break;
  default:
    print_error_and_exit("Instruction %s / %d not yet implemented",
                         format_hex_string(state.ins.opcode), reg_args.reg);
    break;
  }
  set_value(state, rm_args, output);
  set_snapshot(state, operation, rm_args.notation);
}
