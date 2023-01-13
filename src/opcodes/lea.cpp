#include "lea.hpp"

void lea8D(State &state) {
  MODRM_SRC_OPCODE(OPERAND_32, LEA_INS, rm_args.mem_addr);
}
