#ifndef OPCODE_OR_H
#define OPCODE_OR_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define OR_INS "or"

void or0C(State &state);
void or0D(State &state);
void or08(State &state);
void or09(State &state);
void or0A(State &state);
void or0B(State &state);

template <typename T>
T perform_or(State &state, OperandSize size, T op1, T op2) {
  T res = op1 | op2;
  set_logical_flags(state, size, res);
  return res;
}

#endif
