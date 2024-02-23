#!/bin/bash

# file: genRandom.sh
# author: Wesely Anastasi
# course: CSI 3336
# due date: 2/13/2024
#
# date modified: 2/13/2024
# - File Created
#
# This script generates a specified number of random numbers within a specified range.

numValues=10
lowerBound=0
upperBound=9999

if [[ $# -ge 1 ]] # If there is at least one argument
then
    numValues=$1
fi

if [[ $# -ge 2 ]] # If there is at least two arguments
then
    lowerBound=$2
fi

if [[ $# -ge 3 ]] # If there is at least three arguments
then
    upperBound=$3
fi

for i in $(seq 1 $numValues)
do
    echo $((RANDOM % ($upperBound - $lowerBound + 1) + $lowerBound))
done