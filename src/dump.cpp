#include "dump.hpp"
#include "utils.hpp"
#include <iomanip>
#include <iostream>

void table_header_printer(const std::string &heading, uint8_t col_width,
                          uint8_t left_padding, uint8_t right_padding) {
  std::cout << std::endl << std::left << std::setw(left_padding) << "|";
  std::cout << heading << std::right << std::setw(right_padding) << "|"
            << std::endl;
  std::cout << "+" << std::setfill('-') << std::setw(col_width) << "+"
            << std::endl;
}

void table_row_printer(const std::string &name, uint8_t name_width,
                       const std::string &val, uint8_t val_width) {
  std::cout << std::setfill(' ') << "|" << std::left << std::setw(name_width)
            << name << "|";
  std::cout << std::right << std::setw(val_width) << val << "|" << std::endl;
}

void instruction_dump(std::list<Snapshot> snapshots) {
  std::cout << "=======INSTRUCTIONS=======" << std::endl;
  for (Snapshot s : snapshots) {
    std::cout << std::setw(8) << std::right << std::hex << s.start_eip << ":";
    std::cout << " " << std::setw(16) << std::left << s.byte_sequence;
    std::cout << s.instruction << std::endl;
  }
  std::cout << std::endl;
}

void step_transition(std::list<Snapshot> snapshots) {
  std::cout << "Press Enter to display transitions in  next instruction..."
            << std::endl;
  for (Snapshot snapshot : snapshots) {
    getchar();
    std::cout << std::setw(8) << std::right << std::hex << snapshot.start_eip
              << ":";
    std::cout << " " << std::setw(16) << std::left << snapshot.byte_sequence;
    std::cout << snapshot.instruction << std::endl;
    if (!snapshot.reg_transition.empty())
      table_row_printer("reg", 5, snapshot.reg_transition, 30);
    if (!snapshot.mem_transition.empty())
      table_row_printer("mem", 5, snapshot.mem_transition, 30);
    for (std::string f : snapshot.flag_transitions) {
      if (!f.empty())
        table_row_printer("flag", 5, f, 30);
    }
    table_row_printer("eip", 5, snapshot.eip_transition, 30);
    std::cout << std::endl;
  }
  getchar();
}
