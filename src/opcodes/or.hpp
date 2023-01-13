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
T perform_or(State &state, OperandSize size, uint32_t op1, uint32_t op2);

#endif
