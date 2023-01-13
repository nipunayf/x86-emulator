#ifndef OPCODE_JMP_H
#define OPCODE_JMP_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define JMP_INS "jmp"

void jmpEB(State &state);
void jmpE9(State &state);
void jc72(State &state);
void jae73(State &state);
void je74(State &state);
void jbe76(State &state);
void ja77(State &state);
void jl7C(State &state);
void jge7D(State &state);
void jg7F(State &state);
void jecxzE3(State &state);

#define JUMP(bytes, ins_name, cond)                                            \
  uint8_t displacement = state.ins_fetcher.next_nbytes(bytes);                 \
  if (cond)                                                                    \
    state.ins_fetcher.jump_byte(displacement);                                 \
  set_snapshot(state, ins_name, format_immediate(displacement));

#define JUMP_REL8(ins_name, cond) JUMP(1, ins_name, cond)

#define JUMP_REL32(ins_name, cond) JUMP(4, ins_name, cond)

#endif
