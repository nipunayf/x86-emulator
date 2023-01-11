#ifndef OPCODE_ADD_H
#define OPCODE_ADD_H

#include "../handler.hpp"
#include "../modrm.hpp"

int32_t perform_add(State &state, OperandSize op_size, int32_t op1,
                    int32_t op2);
void add03(State &state);
void add05(State &state);

#endif
