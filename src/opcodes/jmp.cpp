#include "jmp.hpp"

void jmpEB(State &state) {
  uint8_t displacement = state.ins_fetcher.next_byte();
  state.ins_fetcher.jump_byte(displacement);
  set_snapshot(state, JMP_INS, format_immediate(displacement));
}
