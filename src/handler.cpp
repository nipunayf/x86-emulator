#include "handler.hpp"

void set_snapshot(State &state, const std::string &ins_name,
                  const std::string &dest, const std::string &source) {

  state.ins.snapshot.instruction =
    dest.empty()
      ? ins_name
      : (source.empty() ? format_instruction(ins_name, dest)
                        : format_instruction(ins_name, source, dest));

  state.snapshots.push_back(state.ins.snapshot);
  state.ins = {};
}

void set_common_arithmetic_flags(State &state, OperandSize op_size,
                                 uint64_t op1, uint64_t op2, uint64_t res) {
  // Set parity flag (PF)
  // Check if the least-significant byte of result contains even number of 1s
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, PF,
                          !__builtin_parity(res & MASK8));

  // Set sign flag (SF)
  // This bit corresponds to the msb of the result
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, SF,
                          read_msb(op_size, res));

  // Set zero flag (ZF)
  // Set if the result is 0
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, ZF, res == 0);
}
