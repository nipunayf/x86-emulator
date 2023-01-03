#ifndef SIB_H
#define SIB_H

#include "register_bank.hpp"

uint32_t process_sib(const uint8_t &sib, RegisterBank &reg_bank);

#endif
