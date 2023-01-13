#ifndef OPCODE_FLAGS_H
#define OPCODE_FLAGS_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define STC_INS "stc"
#define CLC_INS "clc"
#define CMC_INS "cmc"

void stc(State &state);
void clc(State &state);
void cmc(State &state);

#define SET_FLAG(val, ins_name)                                                \
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, val);       \
  set_snapshot(state, ins_name);

#endif
