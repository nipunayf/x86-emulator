#include "opcode.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string file_name = argc > 1 ? argv[1] : "";

  Scanner scanner(file_name);
  RegisterBank reg_bank;
  Memory memory;
  State state{scanner, reg_bank, memory};
  parse(state);

  for (const Snapshot &snapshot : state.snapshots) {
    std::cout << snapshot.instruction << std::endl
              << snapshot.reg_transition << std::endl;
    std::cout << "Flag changes:" << std::endl;
    for (const std::string &flag_change : snapshot.flag_transitions) {
      std::cout << flag_change << std::endl;
    }
  }

  return 0;
}
