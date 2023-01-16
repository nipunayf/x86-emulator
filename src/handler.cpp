#include "handler.hpp"

void set_snapshot(State &state, const std::string &ins_name,
                  const std::string &dest, const std::string &source) {

  // Format the eip transition for the instruction
  uint32_t last_eip = state.reg_bank.load_eip();
  state.ins.snapshot.eip_transition =
    format_register_change(state.reg_bank.name_eip(state.mode),
                           state.ins.snapshot.start_eip, last_eip);

  // Format the assembly instruction
  state.ins.snapshot.instruction =
    dest.empty()
      ? ins_name
      : (source.empty() ? format_instruction(ins_name, dest)
                        : format_instruction(ins_name, dest, source));

  // Set the byte sequence
  state.ins.snapshot.byte_sequence = state.ins_fetcher.get_byte_sequence();

  state.snapshots.push_back(state.ins.snapshot);
}

void set_common_arithmetic_flags(State &state, OperandSize op_size,
                                 uint64_t res) {
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

void set_logical_flags(State &state, OperandSize op_size, uint64_t res) {
  set_common_arithmetic_flags(state, op_size, res);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF, 0);
  state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, 0);
}
