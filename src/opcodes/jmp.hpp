#ifndef OPCODE_JMP_H
#define OPCODE_JMP_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define JMP_INS "jmp"

void jmpEB(State &state);
void jmpE9(State &state);

#define RELATIVE_JUMP(bytes, ins_name)                                         \
  uint8_t displacement = state.ins_fetcher.next_nbytes(bytes);                 \
  state.ins_fetcher.jump_byte(displacement);                                   \
  set_snapshot(state, ins_name, format_immediate(displacement));

#endif
