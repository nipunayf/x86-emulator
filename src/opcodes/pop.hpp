#ifndef OPCODE_POP_H
#define OPCODE_POP_H

#include "../handler.hpp"
#include "../modrm.hpp"

uint32_t perform_pop(State &state);
void pop5x(State &state);
void pop1F(State &state);
void pop07(State &state);
void pop17(State &state);
void pop0FA1(State &state);
void pop0FA9(State &state);

#endif
