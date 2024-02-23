#!/bin/bash

# file: pwopt.sh
# author: Wesely Anastasi
# course: CSI 3336
# due date: 2/16/2024
#
# date modified: 2/16/2024
# - File Created
#
# This script presents a simple interface to print files with options

if [[ $# -lt 2 || $# -gt 3 ]]
then
    >&2 echo "Usage: pwopt.sh <option> <fileName>, options are -duplex, -nUp #, -copy #"
    exit 1
fi

if [[ $# -eq 2 ]]
then
    if [[ $1 == "-duplex" ]]
    then #prints in duplex mode
        echo "Printing in duplex mode"
        lpr -o sides=two-sided-long-edge $2
    else
        >&2 echo "Usage: pwopt.sh <option> <fileName>, options are -duplex, -nUp #, -copy #"
        exit 1
    fi
else
    if [[ $1 == "-nUp" ]]
    then #prints with a border and top to bottom, left to right layout
        echo "Printing $3 in $2-up mode"
        lpr -o page-border=single -o number-up-layout=tblr -o number-up=$2 $3 
    elif [[ $1 == "-copy" ]]
    then #prints $2 copies of the file
        echo "Printing $3 $2 times"
        lpr -#$2 $3
    else
        >&2 echo "Usage: pwopt.sh <option> <fileName>, options are -duplex, -nUp #, -copy #"
        exit 1
    fi
fi

