#ifndef MODRM_H
#define MODRM_H

#include "memory.hpp"
#include "register_bank.hpp"

enum addressing_modes {
  REGISTER_INDIRECT,
  ONE_BYTE_DISPLACEMENT,
  FOUR_BYTE_DISPLACEMENT,
  REGISTER_DIRECT
};

void process_modmr(const uint8_t &byte, RegisterBank &reg_bank, Memory &memory,
                   uint32_t &operand_rm, uint32_t &operand_reg);

#endif
