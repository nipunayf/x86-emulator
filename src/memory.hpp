#ifndef MEMORY_H
#define MEMORY_H

#include "operand.hpp"
#include "utils.hpp"
#include <cstdint>
#include <map>

/**
 * Represents the memory component used in the x86 architecture.
 */
class Memory {
private:
  std::map<uint32_t, uint8_t> m_buffer;

public:
  void store(std::string &transition, const uint32_t &address,
             const uint32_t &data, const OperandSize &size);
  void store8(std::string &transition, const uint32_t &address,
              const uint8_t &data);
  void store16(std::string &transition, const uint32_t &address,
               const uint16_t &data);
  void store32(std::string &transition, const uint32_t &address,
               const uint32_t &data);

  uint32_t load(const uint32_t &address, const OperandSize &size);
  uint8_t load8(const uint32_t &address);
  uint16_t load16(const uint32_t &address);
  uint32_t load32(const uint32_t &address);

  void memory_dump(uint32_t start_eip, uint32_t end_eip);
};

#endif
