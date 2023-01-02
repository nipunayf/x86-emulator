#ifndef HANDLER_H
#define HANDLER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include "scanner.hpp"

#define MAX_PREFIX_COUNT 4

struct Argument {
  uint8_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
};

using handler = void (*)(Argument *args, Scanner *scanner,
                         RegisterBank *register_bank, Memory *memory);

#endif
