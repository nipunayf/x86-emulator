#ifndef OPCODE_IMM_H
#define OPCODE_IMM_H

#include "../handler.hpp"
#include "../modrm.hpp"

void ext80(State &state);
void ext81(State &state);
void ext83(State &state);
void extFF(State &state);
void ext8F(State &state);

#endif
