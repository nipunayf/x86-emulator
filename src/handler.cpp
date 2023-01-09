#include "handler.hpp"
#include <map>

std::map<OperandSize, uint8_t> msb_map = {
  {OPERAND_8, 7}, {OPERAND_16, 15}, {OPERAND_32, 31}, {OPERAND_64, 63}};

uint8_t read_msb(OperandSize op_size, uint64_t value) {
  return (value & (1ul << msb_map[op_size])) > 0;
}

void set_snapshot(State &state, const std::string &ins_name,
                  uint32_t reg_before, uint32_t reg_after,
                  const std::string &dest_reg, const std::string &source_reg) {

  const std::string instruction =
    source_reg.empty() ? format_instruction(ins_name, dest_reg)
                       : format_instruction(ins_name, source_reg, dest_reg);

  Snapshot snapshot{instruction,
                    format_register_change(dest_reg, reg_before, reg_after)};
  state.snapshots.push_back(snapshot);
}

void set_common_arithmetic_flags(RegisterBank &reg_bank, OperandSize op_size,
                                 uint64_t op1, uint64_t op2, uint64_t res) {
  // Set parity flag (PF)
  // Check if the lsb of result contains even number of 1s
  uint64_t y = res;
  for (int i = 1; i <= 16; i *= 2)
    y ^= (y >> i);
  reg_bank.set_flag(PF, y & 1);

  // Set sign flag (SF)
  // This bit corresponds to the msb of the result
  reg_bank.set_flag(SF, read_msb(op_size, res));

  // Set zero flag (ZF)
  // Set if the result is 0
  reg_bank.set_flag(ZF, res == 0);

  // Set overflow flag (OF)
  // When two positive integers or two negative integer operands produce a
  // result with a complemented msb
  reg_bank.set_flag(OF, read_msb(op_size, op1) == read_msb(op_size, op2) &&
                          read_msb(op_size, res) != read_msb(op_size, op1));
}
