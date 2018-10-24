#include <iostream>
#include <cassert>

#include "shared_ring_buffer.h"

std::size_t const buf_sz = 100;

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  buffer.create(buf_sz);

  while(true){
    if(buffer.getCount() >= buf_sz) break;
    int val = 0;
    std::cout << "Integer to enque: ";
    std::cin >> val;
    if(!std::cin.good()) break;
    buffer.enqueue(val);
    std::cout << "Enqueued: " << val << std::endl;
  }

  return 0;
}
