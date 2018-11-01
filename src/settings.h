# pragma once
#include "converters.h"

class Settings
{
public:
  Settings(int argc, char* argv[]);

  uint64_t get_generators_count() const {return m_generators_count;}
  uint64_t get_processors_count() const {return m_processors_count;}
  uint64_t get_block_size() const {return m_block_size;}
  uint64_t get_blocks_count() const {return m_blocks_count;}

private:
  uint64_t m_generators_count = 0;
  uint64_t m_processors_count = 0;
  uint64_t m_block_size = 0;
  uint64_t m_blocks_count = 0;
};
