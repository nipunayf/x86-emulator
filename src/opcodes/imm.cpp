#include "imm.hpp"
#include <cmath>

uint32_t read_immediate(Scanner &scanner, OperandSize type) {
  return scanner.next_nbytes(pow(2, type));
}

void imm(State &state, OperandSize reg_type, OperandSize im_type) {
  ModRMAttribute rm_args{reg_type}, reg_args{im_type};
  process_modrm(state, rm_args, reg_args, true);
  uint32_t immediate =  read_immediate(state.scanner, OPERAND_8);
  std::string operation;
  uint32_t output;
  switch (reg_args.val) {
    case 0:
        operation = "ADD";
        output = rm_args.val + immediate;
        break;
    case 1:
        operation = "OR";
        output = rm_args.val | immediate;
        break;
    case 2:
        operation = "ADC";
        output = rm_args.val + immediate;
        break;
    case 3:
        operation = "SBB";
        output = rm_args.val + immediate;
        break;
    case 4:
        operation = "AND";
        output = rm_args.val & immediate;
        break;
    case 5:
        operation = "SUB";
        output = rm_args.val - immediate;
        break;
    case 6:
        operation = "XOR";
        output = rm_args.val ^ immediate;
        break;
    case 7:
        operation = "CMP";
        output = rm_args.val == immediate;
        break;
  }
  set_value(state, rm_args, output);
  set_snapshot(state, operation, rm_args.val, output, format_immediate(immediate), rm_args.name);
}

void imm80(State &state) {
  imm(state, OPERAND_8, OPERAND_8);
}

void imm81(State &state) {
  imm(state, OPERAND_32, OPERAND_32);
}

void imm83(State &state) {
  imm(state, OPERAND_32, OPERAND_8);
}
