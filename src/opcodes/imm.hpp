#ifndef OPCODE_IMM_H
#define OPCODE_IMM_H

#include "../handler.hpp"
#include "../modrm.hpp"

void imm80(State &state);
void imm81(State &state);
void imm83(State &state);

#endif
