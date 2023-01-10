#ifndef MEMORY_H
#define MEMORY_H

#include "utils.hpp"
#include <cstdint>
#include <map>

class Memory {
private:
  std::map<uint32_t, uint32_t> buffer;

public:
  void store(std::string &transition, const uint32_t &address,
             const uint32_t &data);
  uint32_t read(const uint32_t &address);
};

#endif
