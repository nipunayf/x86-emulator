#ifndef MODRM_H
#define MODRM_H

#include "handler.hpp"

enum AddressingMode {
  REGISTER_INDIRECT,
  ONE_BYTE_DISPLACEMENT,
  FOUR_BYTE_DISPLACEMENT,
  REGISTER_DIRECT
};

enum RegisterType { REGISTER_8, REGISTER_16, REGISTER_32, REGISTER_64 };

struct ModRMAttribute {
  RegisterType type;
  uint32_t val;
  uint32_t addr;
  std::string name;
  bool is_reg = true;
};

void process_modrm(State &state, ModRMAttribute &rm_args,
                   ModRMAttribute &reg_args);

void set_value(State &state, ModRMAttribute &args, uint32_t value);

#endif
