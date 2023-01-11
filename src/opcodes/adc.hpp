#ifndef OPCODE_ADC_H
#define OPCODE_ADC_H

#include "../handler.hpp"
#include "../modrm.hpp"
#include "add.hpp"

#define ADC_INS "adc"

void adc10(State &state);
void adc11(State &state);
void adc12(State &state);
void adc13(State &state);
void adc14(State &state);
void adc15(State &state);

template <typename T>
T perform_adc(State &state, OperandSize op_size, T op1, T op2) {
  return perform_add<T>(state, op_size, op1,
                        op2 + state.reg_bank.load_flag(CF));
}

#endif
