#ifndef MODRM_H
#define MODRM_H

#include "memory.hpp"
#include "register_bank.hpp"

// Addressing modes
#define REGISTER_INDIRECT      0
#define ONE_BYTE_DISPLACEMENT  1
#define FOUR_BYTE_DISPLACEMENT 2
#define REGISTER_DIRECT        3

void processModRM(const uint8_t &byte, RegisterBank &regBank, Memory &memory,
                  uint32_t &operandRM, uint32_t &operandReg);

#endif
