#ifndef MODRM_H
#define MODRM_H

#include "handler.hpp"

enum AddressingMode {
  REGISTER_INDIRECT,
  ONE_BYTE_DISPLACEMENT,
  FOUR_BYTE_DISPLACEMENT,
  REGISTER_DIRECT
};

enum OperandSize { OPERAND_8, OPERAND_16, OPERAND_32, OPERAND_64 };

struct ModRMAttribute {
  OperandSize type;
  uint32_t val;
  uint32_t addr;
  std::string name;
  bool is_reg = true;
};

void process_modrm(State &state, ModRMAttribute &rm_args,
                   ModRMAttribute &reg_args, bool has_extension = false);

void set_value(State &state, ModRMAttribute &args, uint32_t value);

#endif
