#include "generator_task.h"

#include <algorithm>

#include "logger.h"

GeneratorTask::GeneratorTask(MessageQueue<DataBlock> &target, uint64_t block_size, uint64_t blocks_count) : m_target_queue(target), m_block_size(block_size), m_block_count(blocks_count){}

void GeneratorTask::Run() {
  while(m_block_count)
  {
    std::lock_guard<std::mutex> lock(m_count_mutex);
    if(0 == m_block_count) break;

    m_target_queue.AddMessage({--m_block_count, GenerateBlock()});
  }
  LOG_IT(__FUNCTION__  << " end generating ");
}

std::vector<uint8_t> GeneratorTask::GenerateBlock(){
  std::vector<uint8_t> data;
  data.resize(m_block_size);
  std::generate_n(data.begin(), m_block_size, [](){return rand();});
  return data;
}
