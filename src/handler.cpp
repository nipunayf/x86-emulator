#include "handler.hpp"

void set_snapshot(Argument &args, const std::string &ins_name,
                  uint32_t reg_before, uint32_t reg_after,
                  const std::string &first_reg, const std::string &second_reg) {

  const std::string instruction =
    second_reg.empty() ? format_instruction(ins_name, first_reg)
                       : format_instruction(ins_name, first_reg, second_reg);

  Snapshot snapshot{instruction,
                    format_register_change(first_reg, reg_before, reg_after)};
  args.snapshots.push_back(snapshot);
}
