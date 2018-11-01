#pragma once

#include <atomic>

#include "message_queue.h"
#include "data_block.h"
#include "crc32.h"
#include "barrier.h"

class ProcessorTask
{
public :
  ProcessorTask(std::vector<CRC32_sum>& sums, Barrier& final_barrier);
  void Run();

  void AddToProcess(DataBlock& block);

  void Join();

private:
  MessageQueue<DataBlock> m_blocks_queue;
  std::atomic_bool m_is_joined;
  std::vector<CRC32_sum>& m_sums;
  Barrier& m_final;
};
