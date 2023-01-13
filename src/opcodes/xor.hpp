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
T perform_xor(State &state, OperandSize size, uint32_t op1, uint32_t op2);

#endif
