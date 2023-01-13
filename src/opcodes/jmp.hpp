#ifndef OPCODE_JMP_H
#define OPCODE_JMP_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define JMP_INS "jmp"

void jmpEB(State &state);

#endif
