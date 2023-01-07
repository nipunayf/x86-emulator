#include "add.hpp"
#include <iostream>

void add03(State &state) {
  uint32_t rm, reg;
  ModRMAttribute args{rm, reg, REGISTER_32, REGISTER_32};
  process_modrm(state, args);

  uint32_t output = args.rm_val + args.reg_val;
  set_value(state, args.reg_type, args.reg_addr, output, true);

  set_snapshot(state, "add", args.reg_val, output, args.reg_name, args.rm_name);

  for (const Snapshot &snapshot : state.snapshots) {
    std::cout << snapshot.instruction << std::endl
              << snapshot.reg_change << std::endl;
  }
}

void add05(State &state) {
  uint32_t reg = state.reg_bank.load32(EAX);
  uint32_t displace = state.scanner.next_nbytes(4);

  uint32_t output = reg + displace;
  state.reg_bank.set32(EAX, output);

  set_snapshot(state, "add", reg, output, format_displacement(displace),
               state.reg_bank.name32(EAX));
}

void add83(State &state) {
  uint32_t rm, reg;
  ModRMAttribute args{rm, reg, REGISTER_32, REGISTER_32};
  process_modrm(state, args);
  uint32_t displace = state.scanner.next_nbytes(1);

  uint32_t output = args.rm_val + displace;
  set_value(state, args.rm_type, args.rm_addr, output, args.is_reg);

  set_snapshot(state, "add", args.rm_val, output, format_displacement(displace),
               args.rm_name);
}
