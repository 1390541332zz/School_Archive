#!/bin/bash
#===============================================================================
# testrunner.sh: Basic Test Runner for Integration Tests
#
# Usage: testrunner.sh <Wrapper Command> <Slave Command> <Input File>
#                      <Output File>
#===============================================================================

wrapper_cmd=$1
slave_cmd=$2
input_file=$3
output_file=$4

if [[ $output_file != /dev/null ]]; then
    rm $output_file
fi
while read args
do
    $wrapper_cmd $slave_cmd -f ./test/generated/todo.txt $args >> $output_file
done < "$input_file"
rm ./test/generated/todo.txt
