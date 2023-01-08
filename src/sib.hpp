#ifndef SIB_H
#define SIB_H

#include "register_bank.hpp"
#include "utils.hpp"
#include <string>

uint32_t process_sib(const uint8_t &sib, RegisterBank &reg_bank,
                     std::string &name, uint32_t displacement = 0);

#endif
