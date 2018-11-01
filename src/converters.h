#pragma once

#include <stdlib.h>
#include <stdint.h>

namespace {

template<class T>
T fromString(char* sz)
{
  return 0;
}

template<>
uint64_t fromString(char* sz)
{
#if __WORDSIZE == 64
  return strtoul(sz, nullptr, 0);
#else
  return strtoull(sz, nullptr, 0);
#endif
}

}  // namespace
