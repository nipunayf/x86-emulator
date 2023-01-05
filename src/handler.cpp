#include "handler.hpp"
#include <iostream>

void set_snapshot(Argument &args, const std::string &instruction,
                  const std::string &reg_change,
                  const std::string &flag_change) {
  Snapshot snapshot{instruction, reg_change, flag_change};
  args.snapshots.push_back(snapshot);
}
