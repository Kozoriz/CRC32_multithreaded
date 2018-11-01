#pragma once

#include <string>
#include <vector>

typedef uint64_t CRC32_sum;
typedef std::vector<std::vector<CRC32_sum>> ChecksumMatrix;

class CRC32
{
public:
  static CRC32_sum calculate(const std::vector<uint8_t>& data){return Crc32_calc(data.data(), data.size());}


  // reused
  static uint64_t Crc32_calc(const unsigned char *buf, unsigned long len)
  {
    static unsigned long crc_table[256];
    unsigned long crc;

    for (int i = 0; i < 256; i++)
    {
      crc = i;
      for (int j = 0; j < 8; j++)
        crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

      crc_table[i] = crc;
    }

    crc = 0xFFFFFFFFUL;

    while (len--)
      crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
  }
};
