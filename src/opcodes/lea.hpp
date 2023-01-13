#ifndef OPCODE_LEA_H
#define OPCODE_LEA_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define LEA_INS "lea"

void lea8D(State &state);

#endif
