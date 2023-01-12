#ifndef OPCODE_EXTENSION_H
#define OPCODE_EXTENSION_H

#include "../handler.hpp"
#include "../modrm.hpp"

void ext80(State &state);
void ext81(State &state);
void ext83(State &state);
void extFE(State &state);
void extFF(State &state);
void ext8F(State &state);
void extC6(State &state);
void extC7(State &state);

#endif
