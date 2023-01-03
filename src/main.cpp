#include "opcode.hpp"

int main(int argc, char *argv[]) {
  std::string file_name = argc > 1 ? argv[1] : "";

  Scanner scanner(file_name);
  parse(scanner);

  return 0;
}
