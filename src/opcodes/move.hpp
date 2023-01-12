#ifndef OPCODE_MOV_H
#define OPCODE_MOV_H

#include "../handler.hpp"

#define MOV_INS "mov"

void mov88(State &state);
void mov89(State &state);
void mov8A(State &state);
void mov8B(State &state);
void mov8C(State &state);
void mov8E(State &state);
void movA0_A1(State &state);
void movA2_A3(State &state);
void movBx(State &state);
void movCx(State &state);

#endif
