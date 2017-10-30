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

while read args
do
    $wrapper_cmd $slave_cmd $args >> $output_file
done < "$input_file"
