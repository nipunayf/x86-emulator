#include "jmp.hpp"

void jmpEB(State &state) { RELATIVE_JUMP(1, JMP_INS) }

void jmpE9(State &state) { RELATIVE_JUMP(4, JMP_INS) }
