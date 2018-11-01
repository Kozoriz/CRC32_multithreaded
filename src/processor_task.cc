#include "processor_task.h"
#include "logger.h"

ProcessorTask::ProcessorTask(std::vector<CRC32_sum> &sums, Barrier &final_barrier) : m_is_joined(false), m_sums(sums), m_final(final_barrier)
{

}

void ProcessorTask::Run()
{
  while(!m_is_joined || !m_blocks_queue.IsEmpty())
  {
    if(m_blocks_queue.IsEmpty()) continue;
    const DataBlock& block = m_blocks_queue.Front();


    CRC32_sum checksum = CRC32::calculate(block.data);
    m_sums.push_back(checksum);

    m_blocks_queue.Pop();
  }
  m_final.wait();
  LOG_IT("finished processing");
}

void ProcessorTask::AddToProcess(DataBlock &block)
{
  m_blocks_queue.AddMessage(block);
}

void ProcessorTask::Join()
{
  m_is_joined = true;
}
