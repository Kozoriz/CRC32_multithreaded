#include "processor_pool.h"
#include "logger.h"

ProcessorPool::ProcessorPool(uint64_t processors_count, MessageQueue<DataBlock> &message_queue)
  : m_target_queue(message_queue), m_calculated_sums(processors_count), m_child_threads_waiter(processors_count + 1) {

  for(uint64_t i = 0; i < processors_count; ++i)
  {
    m_processors.push_back(std::make_unique<ProcessorTask>(m_calculated_sums[i],m_child_threads_waiter));
    m_processor_threads.push_back(std::thread(&ProcessorTask::Run, m_processors[i].get()));
  }
}

ProcessorPool::~ProcessorPool()
{
  for(auto& proc : m_processor_threads)
  {
    proc.join();
  }
}

void ProcessorPool::ProcessMessages(){
  while(!m_target_queue.IsEmpty())
  {
    DataBlock block = m_target_queue.GetMessage();
    LOG_IT("Message " << block.id << " added to processing");
    for(auto& proc : m_processors)
    {
      proc->AddToProcess(block);
    }
  }

  for(auto& proc : m_processors)
  {
    proc->Join();
  }
  m_child_threads_waiter.wait();
}

void ProcessorPool::CheckSums()
{
  LOG_IT("Checking calculated values");
  for(size_t i = 0; i < m_calculated_sums[0].size(); ++i)
  {
    for(size_t proc_id = 0; proc_id < m_processors.size() - 1; ++proc_id)
    {
      LOG_IT(m_calculated_sums[proc_id][i] <<  " "  << m_calculated_sums[proc_id + 1][i]);
      if(m_calculated_sums[proc_id][i] != m_calculated_sums[proc_id + 1][i])
      {
        LOG_IT(proc_id << " checksum did not match");
      }
    }
  }
}
