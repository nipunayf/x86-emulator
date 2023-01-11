#include "adc.hpp"

#define ADDC_INS "adc"

void adc10(State &state) {
  MODRM_DEST_OPCODE(state, OPERAND_8, ADDC_INS,
                    perform_adc<int8_t>(state, OPERAND_8, (int8_t)rm_args.val,
                                        (int8_t)reg_args.val))
}

void adc11(State &state) {
  MODRM_DEST_OPCODE(state, OPERAND_32, ADDC_INS,
                    perform_adc<int32_t>(state, OPERAND_32,
                                         (int32_t)rm_args.val,
                                         (int32_t)reg_args.val));
}

void adc12(State &state) {
  MODRM_SRC_OPCODE(state, OPERAND_8, ADDC_INS,
                   perform_adc<int8_t>(state, OPERAND_8, (int8_t)reg_args.val,
                                       (int8_t)rm_args.val));
}

void adc13(State &state) {
  MODRM_OPCODE(state, OPERAND_32,
               perform_adc<int32_t>(state, OPERAND_32, (int32_t)rm_args.val,
                                    (int32_t)reg_args.val),
               reg_args, ADDC_INS, reg_args.notation, rm_args.notation)
}

void adc14(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    state, int8_t, OPERAND_8, AL, 1, ADDC_INS,
    perform_adc<int8_t>(state, OPERAND_8, reg_val, displace))
}

void adc15(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    state, int32_t, OPERAND_32, EAX, 4, ADDC_INS,
    perform_adc<int32_t>(state, OPERAND_32, reg_val, displace))
}
