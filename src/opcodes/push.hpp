#ifndef OPCODE_PUSH_H
#define OPCODE_PUSH_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define PUSH_INS "push"

void perform_push(State &state, uint32_t val, std::string notation);

void push5x(State &state);
void push6A(State &state);
void push68(State &state);
void push0E(State &state);
void push16(State &state);
void push1E(State &state);
void push06(State &state);
void push0FA0(State &state);
void push0FA8(State &state);

#endif
