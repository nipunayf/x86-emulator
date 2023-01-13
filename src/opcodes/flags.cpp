#include "flags.hpp"

void stc(State &state) { SET_FLAG(1, STC_INS) }

void clc(State &state) { SET_FLAG(0, CLC_INS) }

void cmc(State &state) { SET_FLAG(!state.reg_bank.load_flag(CF), CMC_INS) }
