#include "opcode.hpp"

int main(int argc, char *argv[]) {
  std::string file_name = argc > 1 ? argv[1] : "";

  Scanner scanner(file_name);
  RegisterBank reg_bank;
  Memory memory;
  Argument args{scanner, reg_bank, memory};
  parse(args);

  return 0;
}
