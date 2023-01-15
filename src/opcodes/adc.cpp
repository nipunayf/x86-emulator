#include "adc.hpp"

void adc10(State &state) {
  MODRM_DEST_OPCODE(OPERAND_8, ADC_INS,
                    perform_adc<uint8_t>(state, OPERAND_8, (uint8_t)rm_args.val,
                                         (uint8_t)reg_args.val))
}

void adc11(State &state) {
  MODRM_DEST_OPCODE(OPERAND_32, ADC_INS,
                    perform_adc<uint32_t>(state, OPERAND_32,
                                          (uint32_t)rm_args.val,
                                          (uint32_t)reg_args.val));
}

void adc12(State &state) {
  MODRM_SRC_OPCODE(OPERAND_8, ADC_INS,
                   perform_adc<uint8_t>(state, OPERAND_8, (uint8_t)reg_args.val,
                                        (uint8_t)rm_args.val));
}

void adc13(State &state) {
  MODRM_OPCODE(OPERAND_32,
               perform_adc<uint32_t>(state, OPERAND_32, (uint32_t)reg_args.val,
                                     (uint32_t)rm_args.val),
               reg_args, ADC_INS, reg_args.notation, rm_args.notation)
}

void adc14(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    uint8_t, OPERAND_8, AL, 1, ADC_INS,
    perform_adc<uint8_t>(state, OPERAND_8, reg_val, displace))
}

void adc15(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    uint32_t, OPERAND_32, EAX, 4, ADC_INS,
    perform_adc<uint32_t>(state, OPERAND_32, reg_val, displace))
}
