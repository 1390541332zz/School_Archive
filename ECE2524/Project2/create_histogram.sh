#!/bin/bash

declare outfile="./hist.dat"
declare plotfile="./hist_rand.plt"

print_stats () {
    local -n arr=$2
    local sz="${#arr[*]}" 
    local avg='0'
    local min='101'
    local max='-1'
    for i in "${arr[@]}"; do
        let "avg += $i"
        if [ $i -gt $max ]; then
            let "max = $i"
        fi

        if [ $i -lt $min ]; then
            let "min = $i"
        fi
    done
    let "avg /= $sz"

    echo "$1: $sz"
    echo "${arr[@]}"
    echo "avg: $avg"
    echo "min: $min"
    echo "max: $max"
    echo ''
}

declare -a bin_rand;
declare -a bin_20;
declare -a bin_40;
declare -a bin_60;
declare -a bin_80;
declare -a bin_100;

for i in `seq 1 100`; do
    bin_rand+=( $((RANDOM % 101)) )
done 

for i in "${bin_rand[@]}"; do
    if [ $i -lt 20 ]; then
        bin_20+=($i)
    elif [ $i -lt 40 ]; then
        bin_40+=($i)
    elif [ $i -lt 60 ]; then
        bin_60+=($i)
    elif [ $i -lt 80 ]; then
        bin_80+=($i)
    else
        bin_100+=($i)
    fi
done

echo "100 random numbers in the range [0-100]:"
echo "${bin_rand[@]}"
echo ''

print_stats 'bin_20' bin_20
print_stats 'bin_40' bin_40
print_stats 'bin_60' bin_60
print_stats 'bin_80' bin_80
print_stats 'bin_100' bin_100

echo 'bins "number of arguments"' > "$outfile" 
echo "20 ${#bin_20[*]}"          >> "$outfile" 
echo "40 ${#bin_40[*]}"          >> "$outfile" 
echo "60 ${#bin_60[*]}"          >> "$outfile" 
echo "80 ${#bin_80[*]}"          >> "$outfile" 
echo "100 ${#bin_100[*]}"        >> "$outfile"

gnuplot "$plotfile"
