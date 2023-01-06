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

struct ModmrAttribute {
  uint32_t &reg_ptr;
  uint32_t &rm_ptr;
  RegisterType reg_type;
  RegisterType rm_type;
  std::string reg_name;
  std::string rm_name;
};

void process_modmr(State &state, ModmrAttribute &args);

#endif
