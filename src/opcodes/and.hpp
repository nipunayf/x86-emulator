#ifndef OPCODE_AND_H
#define OPCODE_AND_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define AND_INS "and"

void and24_25(State &state);
void and20(State &state);
void and21(State &state);
void and22(State &state);
void and23(State &state);

template <typename T>
T perform_and(State &state, OperandSize size, uint32_t op1, uint32_t op2);

#endif