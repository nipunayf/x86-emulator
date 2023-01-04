#ifndef HANDLER_H
#define HANDLER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include "scanner.hpp"

#define MAX_PREFIX_COUNT 4

struct Argument {
  Scanner &scanner;
  RegisterBank &reg_bank;
  Memory &memory;
  uint8_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
};

using Handler = void (*)(Argument &args);

#endif
