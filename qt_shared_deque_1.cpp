#include <iostream>
#include <cassert>

#include "shared_ring_buffer.h"

std::size_t const buf_sz = 100;

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  buffer.create(buf_sz);

  while(true){
    if(buffer.getCount() > 0){
      int value = buffer.dequeue();
      std::cout << "Dequeued: " << value << std::endl;
      break;
    }
  }
  
  return 0;
}
