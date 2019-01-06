#!/bin/bash

BLOCK_SZ=32;
MISS_PENALTY=40;

cache_arr=(256 128 64 32 16  8);
assoc_arr=(  1   2  4  8 16 32);

echo 'Cache Scan on art.trace' > ./cache.out;
for i in ${!cache_arr[*]}; do 
    CACHE_SZ=${cache_arr[$i]};
    ASSOCIATIVITY=${assoc_arr[$i]};
    echo -e "\n( Cache Size: $CACHE_SZ, Assoc: $ASSOCIATIVITY )" >> ./cache.out;
    cat art.trace | ./cachesim -a $ASSOCIATIVITY -s $CACHE_SZ -l $BLOCK_SZ -mp $MISS_PENALTY >> ./cache.out;
done
