#include "extension.hpp"
#include "add.hpp"
#include "inc.hpp"
#include "pop.hpp"
#include "push.hpp"
#include <cmath>
#include <iostream>

uint32_t read_immediate(Scanner &scanner, OperandSize type) {
  return scanner.next_nbytes((unsigned char)pow(2, type));
}

template <typename T>
void ext8x(State &state, OperandSize reg_type, OperandSize imm_type) {
  ModRMAttribute rm_args{reg_type}, reg_args{reg_type};
  process_modrm(state, rm_args, reg_args);
  T immediate = read_immediate(state.scanner, imm_type);
  std::string operation;
  T res = 0;
  switch (reg_args.reg) {
  case 0:
    operation = "add";
    res = perform_add<T>(state, reg_type, (T)rm_args.val, immediate);
    break;
  default:
    print_error_and_exit("Instruction %d / %d not yet implemented",
                         format_hex_string(state.ins.opcode).c_str(),
                         reg_args.reg);
  }
  set_value(state, rm_args, res);
  set_snapshot(state, operation, rm_args.notation, format_immediate(immediate));
}

void ext80(State &state) { ext8x<int8_t>(state, OPERAND_8, OPERAND_8); }

void ext81(State &state) { ext8x<int32_t>(state, OPERAND_32, OPERAND_32); }

void ext83(State &state) { ext8x<int32_t>(state, OPERAND_32, OPERAND_8); }

void extFE(State &state) {
  ModRMAttribute rm_args{OPERAND_8}, reg_args{OPERAND_8};
  process_modrm(state, rm_args, reg_args);
  std::string operation;
  int8_t res = 0;
  switch (reg_args.reg) {
  case 0:
    res = perform_inc<int8_t>(state, OPERAND_8, (int8_t)rm_args.val);
    operation = "inc";
    break;
  case 1:
    operation = "dec";
    // TODO: Implement DEC instruction
    break;
  default:
    print_error_and_exit("Invalid reg code %s for '0xfe' opcode", reg_args.reg);
  }
  set_value(state, rm_args, res);
  set_snapshot(state, operation, rm_args.notation);
}

void extFF(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);
  std::string operation;
  int32_t res = 0;
  switch (reg_args.reg) {
  case 0:
    res = perform_inc<int32_t>(state, OPERAND_32, (int32_t)rm_args.val);
    operation = "inc";
    break;
  case 6:
    perform_push(state, rm_args.val, rm_args.notation);
    break;
  default:
    print_error_and_exit("Instruction %s / %d not yet implemented",
                         format_hex_string(state.ins.opcode).c_str(),
                         reg_args.reg);
  }
  set_value(state, rm_args, res);
  set_snapshot(state, operation, rm_args.notation);
}

void ext8F(State &state) {
  ModRMAttribute rm_args{OPERAND_32}, reg_args{OPERAND_32};
  process_modrm(state, rm_args, reg_args);
  std::string operation;
  uint32_t output = 0;
  switch (reg_args.reg) {
  case 0:
    operation = "pop";
    output = perform_pop(state);
    break;
  default:
    print_error_and_exit("Instruction %s / %d not yet implemented",
                         format_hex_string(state.ins.opcode).c_str(),
                         reg_args.reg);
  }
  set_value(state, rm_args, output);
  set_snapshot(state, operation, rm_args.notation);
}
