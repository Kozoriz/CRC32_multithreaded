#include "barrier.h"
#include "logger.h"

Barrier::Barrier(std::size_t count) : _count(count) { }

void Barrier::wait()
{
  std::unique_lock<std::mutex> lock(_mutex);
  if (--_count == 0) {
    _cv.notify_all();
  } else {
    _cv.wait(lock, [this] { return _count == 0; });
  }
}
