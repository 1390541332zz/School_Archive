#include <iostream>
#include <cassert>

#include "shared_ring_buffer.h"

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  buffer.create(BUF_SZ);

  while(true){
    if(buffer.getCount() >= BUF_SZ) continue;
    int val = 0;
    std::cout << "Integer to enque: ";
    std::cin >> val;
    if(!std::cin.good()) break;
    buffer.enqueue(val);
    std::cout << "Enqueued: " << val << std::endl;
  }

  return 0;
}
