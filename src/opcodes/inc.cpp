#include "inc.hpp"
#include "iostream"

std::map<int, int> reg_map = {{0x40, EAX}, {0x41, ECX}, {0x42, EDX},
                              {0x43, EBX}, {0x44, ESP}, {0x45, EBP},
                              {0x46, ESI}, {0x47, EDI}};

void inc4x(Argument &args, Scanner &scanner, RegisterBank &register_bank,
           Memory &memory) {
  // TODO: Decode the register operand
  std::cout << "Execute increment operation on a single register" << std::endl;
}
