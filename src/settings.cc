#include "settings.h"
#include "logger.h"

Settings::Settings(int argc, char *argv[])
{
  if(argc < 5)
  {
    LOG_IT("Wrong args count! Correct using : <executable> gen_count proc_count block_size blocks_count");
    return;
  }

  m_generators_count = fromString<uint64_t>(argv[1]);
  m_processors_count = fromString<uint64_t>(argv[2]);
  m_block_size = fromString<uint64_t>(argv[3]);
  m_blocks_count = fromString<uint64_t>(argv[4]);
}
