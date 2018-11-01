#pragma once

#include <condition_variable>
#include <atomic>

class Barrier
{
public:
    explicit Barrier(std::size_t count);
    void wait();
private:
    std::mutex _mutex;
    std::condition_variable _cv;
    std::size_t _count;
};
