#include "jmp.hpp"

void jmpEB(State &state) { JUMP_REL8(JMP_INS, true) }

void jmpE9(State &state) { JUMP_REL32(JMP_INS, true) }

void jc72(State &state) { JUMP_REL8("jc", state.reg_bank.load_flag(CF) == 1) }

void jae73(State &state) { JUMP_REL8("jae", state.reg_bank.load_flag(CF) == 0) }

void je74(State &state) { JUMP_REL8("je", state.reg_bank.load_flag(ZF) == 1) }

void jbe76(State &state) {
  JUMP_REL8("jbe", state.reg_bank.load_flag(CF) == 1 &&
                     state.reg_bank.load_flag(ZF) == 1)
}

void ja77(State &state) {
  JUMP_REL8("ja", state.reg_bank.load_flag(CF) == 0 &&
                    state.reg_bank.load_flag(ZF) == 0)
}

void jl7C(State &state) {
  JUMP_REL8("jl", state.reg_bank.load_flag(SF) != state.reg_bank.load_flag(OF))
}

void jge7D(State &state) {
  JUMP_REL8("jge", state.reg_bank.load_flag(SF) == state.reg_bank.load_flag(OF))
}

void jle7E(State &state) {
  JUMP_REL8("jle",
            state.reg_bank.load_flag(ZF) == 1 ||
              state.reg_bank.load_flag(SF) != state.reg_bank.load_flag(OF))
}

void jg7F(State &state) {
  JUMP_REL8("jg",
            state.reg_bank.load_flag(ZF) == 0 &&
              state.reg_bank.load_flag(SF) == state.reg_bank.load_flag(OF))
}

void jecxzE3(State &state) {
  JUMP_REL8("jecxz", state.reg_bank.load32(ECX) == 0)
}
