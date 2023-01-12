#ifndef OPCODE_NOP_H
#define OPCODE_NOP_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define NOP_INS "nop"

void nop90(State &state);
void nop0F1F(State &state);

#endif
