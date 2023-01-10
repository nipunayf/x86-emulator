#ifndef MODRM_H
#define MODRM_H

#include "handler.hpp"
#include "register_bank.hpp"

#define MEM_ADDR_DEFAULT 0
#define REG_UNSET        32

enum AddressingMode {
  REGISTER_INDIRECT,
  ONE_BYTE_DISPLACEMENT,
  TWO_OR_FOUR_BYTE_DISPLACEMENT,
  REGISTER_DIRECT
};

struct ModRMAttribute {
  OperandSize type;
  uint32_t val;
  std::string notation;
  uint32_t reg = REG_UNSET;
  uint32_t mem_addr = MEM_ADDR_DEFAULT;
};

void process_modrm(State &state, ModRMAttribute &rm_args,
                   ModRMAttribute &reg_args);

void set_value(State &state, ModRMAttribute &args, uint32_t value);

#endif
