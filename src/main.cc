#include <algorithm>

#include "settings.h"
#include "logger.h"

#include "processor_pool.h"
#include "generator_task.h"


int main( int argc, char* argv[] )
{
  Settings settings(argc, argv);

  MessageQueue<DataBlock> blocks_queue;

  GeneratorTask gen_task(blocks_queue, settings.get_block_size(), settings.get_blocks_count());
  std::vector<std::thread> generators;
  generators.resize(settings.get_generators_count());
  std::generate_n(generators.begin(),
                  settings.get_generators_count(),
                  [&gen_task](){return std::thread(&GeneratorTask::Run, &gen_task);});

  ProcessorPool processor(settings.get_processors_count(), blocks_queue);
  processor.ProcessMessages();

  processor.CheckSums();

  for(auto& gen : generators)
  {
    gen.join();
  }

  return 1;
}
