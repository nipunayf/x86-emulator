#include "jmp.hpp"

void jmpEB(State &state) { JUMP(1, JMP_INS, true) }

void jmpE9(State &state) { JUMP(4, JMP_INS, true) }

void jc(State &state) { JUMP(1, "jc", state.reg_bank.load_flag(CF) == 1) }
