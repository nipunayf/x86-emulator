#ifndef HANDLER_H
#define HANDLER_H

#include "memory.hpp"
#include "register_bank.hpp"
#include "scanner.hpp"
#include "utils.hpp"
#include <list>

#define MAX_PREFIX_COUNT 4

struct Snapshot {
  std::string instruction;
  std::string reg_change;
  std::string flag_change;
};

struct Argument {
  Scanner &scanner;
  RegisterBank &reg_bank;
  Memory &memory;
  uint8_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
  std::list<Snapshot> snapshots;
};

using Handler = void (*)(Argument &args);

#endif
