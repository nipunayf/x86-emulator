#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include "register.hpp"
#include <fstream>
#include <string>

#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

class RegisterBank {
  private:
    Register registers[8];
    std::string name;

  public:
    RegisterBank();
    uint32_t loadRegisterValue(int index);
};

#endif
