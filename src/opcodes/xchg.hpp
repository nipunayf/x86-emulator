#ifndef OPCODE_XCHG_H
#define OPCODE_XCHG_H

#include "../handler.hpp"

#define XCHG_INS "xchg"

void xchg9x(State &state);
void xchg86_87(State &state);

#endif
