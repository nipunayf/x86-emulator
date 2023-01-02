#ifndef SIB_H
#define SIB_H

#include "register_bank.hpp"

uint32_t processSIB(const uint8_t &sib, RegisterBank &regBank);

#endif
