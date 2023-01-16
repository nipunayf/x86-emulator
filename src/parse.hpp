#ifndef OPCODE_H
#define OPCODE_H

#include "handler.hpp"

/**
 * Parses a series of instruction.
 *
 * @param state the initial state of the emulator
 * @return
 */
int parse(State &state);

#endif
