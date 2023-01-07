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
  uint8_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
};

struct State {
  Scanner &scanner;
  RegisterBank &reg_bank;
  Memory &memory;
  Argument args;
  std::list<Snapshot> snapshots;
};

using Handler = void (*)(State &args);

void set_snapshot(State &state, const std::string &ins_name,
                  uint32_t reg_before, uint32_t reg_after,
                  const std::string &dest_reg,
                  const std::string &source_reg = "");

#endif
