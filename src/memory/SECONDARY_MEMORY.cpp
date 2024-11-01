#include "SECONDARY_MEMORY.h"
  
void SECONDARY_MEMORY::write(size_t position, uint32_t value)
{
  if (position >= storage.size())
  {
    cerr << "SECONDARY_MEMORY: position out of memory bounds!" << endl;
  }
  else
  {
    storage[position] = value;
  }
}

uint32_t SECONDARY_MEMORY::read(size_t position) const
{
  if (position >= storage.size())
  {
    cerr << "SECONDARY_MEMORY: position out of memory bounds!" << endl;
    return 1;
  }
  
  return storage[position];
}
