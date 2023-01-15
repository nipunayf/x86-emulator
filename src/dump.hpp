#ifndef DUMP_H
#define DUMP_H

#include "handler.hpp"
#include <string>

void table_header_printer(const std::string &heading, uint8_t col_width,
                          uint8_t left_padding, uint8_t right_padding);

void table_row_printer(const std::string &name, uint8_t name_width,
                       const std::string &val, uint8_t val_width);

void instruction_dump(std::list<Snapshot> snapshots);

void step_transition(std::list<Snapshot> snapshots);

#endif
