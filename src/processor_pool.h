#pragma once

#include <thread>

#include "processor_task.h"

class ProcessorPool
{
public :
  ProcessorPool(uint64_t processors_count, MessageQueue<DataBlock>& message_queue);

  ~ProcessorPool();

  void ProcessMessages();

  void CheckSums();

private:
   MessageQueue<DataBlock>& m_target_queue;
   std::vector<std::thread> m_processor_threads;
   std::vector<std::unique_ptr<ProcessorTask> > m_processors;

   ChecksumMatrix m_calculated_sums;

   Barrier m_child_threads_waiter;
};
