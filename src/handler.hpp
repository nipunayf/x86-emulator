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
  std::string reg_transition;
  std::string mem_transition;
  std::list<std::string> flag_transitions;
};

struct Instruction {
  uint8_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
  Snapshot snapshot;
};

struct State {
  Scanner &scanner;
  RegisterBank &reg_bank;
  Memory &memory;
  Instruction args;
  std::list<Snapshot> snapshots;
};

using Handler = void (*)(State &args);

void set_snapshot(State &state, const std::string &ins_name,
                  const std::string &dest, const std::string &source = "");

void set_common_arithmetic_flags(State &state, OperandSize msb, uint64_t op1,
                                 uint64_t op2, uint64_t res);

#endif
