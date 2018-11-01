#pragma once

#include <vector>
#include <stdint.h>

struct DataBlock
{
  uint64_t id;
  std::vector<uint8_t> data;
};
