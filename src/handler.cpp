#include "handler.hpp"

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
  // Check if the least-significant byte of result contains even number of 1s
  reg_bank.set_flag(PF, !__builtin_parity(res & 255));

  // Set sign flag (SF)
  // This bit corresponds to the msb of the result
  reg_bank.set_flag(SF, read_msb(op_size, res));

  // Set zero flag (ZF)
  // Set if the result is 0
  reg_bank.set_flag(ZF, res == 0);
}
