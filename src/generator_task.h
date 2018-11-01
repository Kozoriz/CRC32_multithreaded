#pragma once

#include "message_queue.h"
#include "data_block.h"

class GeneratorTask
{
public :
  GeneratorTask(MessageQueue<DataBlock>& target, uint64_t block_size, uint64_t blocks_count);
  void Run();
  std::vector<uint8_t> GenerateBlock();

private:
  MessageQueue<DataBlock>& m_target_queue;
  uint64_t m_block_size;
  uint64_t m_block_count;
  std::mutex m_count_mutex;
};
