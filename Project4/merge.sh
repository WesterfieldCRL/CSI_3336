#!/bin/bash

# file: merge.sh
# author: Wesely Anastasi
# course: CSI 3336
# due date: 2/19/2024
#
# date modified: 2/19/2024
# - File Created
#
# This script copys all files from directory a and b and merges them into a new directory c

source1=
source2=
destination=
keep=false
larger=false

for arg in $@
do
    if [[ -d $arg ]]
    then
        if [[ $source1 == '' ]]
        then
            source1=$arg
        elif [[ $source2 == '' ]]
        then
            source2=$arg
        else
            >&2 echo "Error 1: Invalid argument"
            exit 1
        fi
    elif [[ $arg == '-keep' && $keep == false ]]
    then
        keep=true
    elif [[ $arg == '-larger' && $larger == false ]]
    then
        larger=true
    elif [[ ! -d $arg && $destination == '' ]]
    then
        destination=$arg
    else
        >&2 echo "Error 2: Invalid argument"
        exit 1
    fi
done

if [[ -d $destination ]]
then
    >&2 echo "Error: $destination already exists"
    exit 1
fi

function mergeNormal {
    for file in $2/*
    do
        if [[ ! -f $3/$(basename $file) ]] # if file does not exist in c
        then
            cp $file $3 # copies new file
        elif [[ $(stat -c %X $file) -gt $(stat -c %X $1/$(basename $file)) ]] # if file is newer
        then
            cp $file $3 # copies new file
        fi
    done
}

function mergeKeep {
    for file in $2/*
    do
        if [[ ! -f $3/$(basename $file) ]] # if file does not exist in c
        then
            cp $file $3 # copies new file
        elif [[ $(stat -c %X $file) -gt $(stat -c %X $1/$(basename $file)) ]] # if file is newer
        then
            mv $3/$(basename $file) $3/$(basename $file).old # renames old file to .old
            cp $file $3 # copies new file
        elif [[ $(stat -c %X $file) -lt $(stat -c %X $1/$(basename $file)) ]] # if file is older
        then
            cp $file $3/$(basename $file).old # renames new file to .old and copies
        fi
    done
}

function mergeLarger {
    for file in $2/*
    do
        if [[ ! -f $3/$(basename $file) || $(stat -c %s $file) -gt $(stat -c %s $3/$(basename $file)) ]] # if file does not exist in c or file is larger
        then
            cp $file $3
        fi
    done
}

function mergeLargerKeep {
    for file in $2/*
    do
        if [[ ! -f $3/$(basename $file) ]]
        then
            cp $file $3
        elif [[ $(stat -c %s $file) -gt $(stat -c %s $3/$(basename $file)) ]] # if file is larger
        then
            mv $3/$(basename $file) $3/$(basename $file).small
            cp $file $3
        elif [[ $(stat -c %s $file) -le $(stat -c %s $3/$(basename $file)) ]] # if file is smaller
        then
            cp $file $3/$(basename $file).small
        fi
    done
}

mkdir $destination

cp -r $source1/* $destination

if [[ $keep == false && $larger == false ]]
then 
    mergeNormal $source1 $source2 $destination

elif [[ $keep == true && $larger == false ]]
then
    mergeKeep $source1 $source2 $destination

elif [[ $keep == false && $larger == true ]]
then
    mergeLarger $source1 $source2 $destination

elif [[ $keep == true && $larger == true ]]
then
    mergeLargerKeep $source1 $source2 $destination
fi