#ifndef MODRM_H
#define MODRM_H

#include "memory.hpp"
#include "register_bank.hpp"
#include "scanner.hpp"

enum AddressingMode {
  REGISTER_INDIRECT,
  ONE_BYTE_DISPLACEMENT,
  FOUR_BYTE_DISPLACEMENT,
  REGISTER_DIRECT
};

void process_modmr(const uint8_t &byte, Scanner &scanner,
                   RegisterBank &reg_bank, Memory &memory, uint32_t &operand_rm,
                   uint32_t &operand_reg);

#endif
