#ifndef OPCODE_CMP_H
#define OPCODE_CMP_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define CMP_INS "cmp"

void cmp3C(State &state);
void cmp3D(State &state);
void cmp38(State &state);
void cmp39(State &state);
void cmp3A(State &state);
void cmp3B(State &state);

#endif
