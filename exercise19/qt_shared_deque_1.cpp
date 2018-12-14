#include <iostream>
#include <cassert>

#include "shared_ring_buffer.h"

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  buffer.create(BUF_SZ);

  while(true){
    if(buffer.getCount() > 0){
      int value = buffer.dequeue();
      std::cout << "Dequeued: " << value << std::endl;
      break;
    }
  }
  
  return 0;
}
