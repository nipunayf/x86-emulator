#ifndef OPCODE_XOR_H
#define OPCODE_XOR_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define XOR_INS "xor"

void xor34(State &state);
void xor35(State &state);
void xor30(State &state);
void xor31(State &state);
void xor32(State &state);
void xor33(State &state);

template <typename T>
T perform_xor(State &state, OperandSize size, T op1, T op2) {
  T res = op1 ^ op2;
  set_logical_flags(state, size, res);
  return res;
}

#endif
