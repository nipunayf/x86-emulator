#ifndef OPCODE_ADD_H
#define OPCODE_ADD_H

#include "../handler.hpp"
#include "../modrm.hpp"

template <typename T>
T perform_add(State &state, OperandSize op_size, T op1, T op2);

void add00(State &state);
void add01(State &state);
void add02(State &state);
void add03(State &state);
void add04(State &state);
void add05(State &state);

#endif
