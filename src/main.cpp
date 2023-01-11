#include "opcode.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string file_name = argc > 1 ? argv[1] : "";

  Scanner scanner(file_name);
  RegisterBank reg_bank;
  Memory memory;
  State state{scanner, reg_bank, memory};
  parse(state);

  return 0;
}
