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
  uint32_t &rm_val;
  uint32_t &reg_val;
  RegisterType rm_type;
  RegisterType reg_type;
  uint32_t rm_addr;
  uint32_t reg_addr;
  std::string rm_name;
  std::string reg_name;
  bool is_reg = false;
};

void process_modrm(State &state, ModRMAttribute &args);

void set_value(State &state, RegisterType type, uint32_t addr, uint32_t value,
               bool is_reg = false);

#endif
