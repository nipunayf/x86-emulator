#ifndef OPCODE_AND_H
#define OPCODE_AND_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define AND_INS "and"

void and24(State &state);
void and25(State &state);
void and20(State &state);
void and21(State &state);
void and22(State &state);
void and23(State &state);

template <typename T>
T perform_and(State &state, OperandSize size, T op1, T op2);

#endif
