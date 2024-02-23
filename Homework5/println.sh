#!/bin/bash

# file: println.sh
# author: Wesely Anastasi
# course: CSI 3336
# due date: 2/16/2024
#
# date modified: 2/16/2024
# - File Created
#
# This script prints the given line from the given file

if [[ $# -lt 2 || $# -gt 2 ]]
then
    >&2 echo "Usage: println.sh <lineNumber> <fileName>"
    exit 1
fi

if [[ $1 -lt 1 ]]
then
    >&2 echo "Error: Line number must be greater than 0"
    exit 1
fi

if [[ ! -f $2 ]]
then
    >&2 echo "Error: File $2 does not exist"
    exit 1
fi

if [[ ! -r $2 ]]
then
    >&2 echo "Error: File $2 is not readable"
    exit 1
fi

line=$(sed -n "$1p" $2)
echo $line