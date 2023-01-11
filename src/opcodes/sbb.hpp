#ifndef OPCODE_SBB_H
#define OPCODE_SBB_H

#include "../handler.hpp"
#include "../modrm.hpp"
#include "sub.hpp"

#define SBB_INS "sbb"

void sbb18(State &state);
void sbb19(State &state);
void sbb1A(State &state);
void sbb1B(State &state);
void sbb1C(State &state);
void sbb1D(State &state);

template <typename T>
T perform_sbb(State &state, OperandSize op_size, T op1, T op2) {
  return perform_sub<T>(state, op_size, op1,
                        op2 + state.reg_bank.load_flag(CF));
}

#endif
