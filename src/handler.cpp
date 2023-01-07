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
