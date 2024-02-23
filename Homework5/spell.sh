#!/bin/bash

# file: spell.sh
# author: Wesely Anastasi
# course: CSI 3336
# due date: 2/16/2024
#
# date modified: 2/16/2024
# - File Created
#
# This script checks the spelling of words passed as arguments using the dictionary file /usr/share/dict/words

if [[ $# -eq 0 ]]
then
    >&2 echo "Usage: spell.sh <word1> <word2> ... <wordN>"
    exit 1
fi

for word in $@
do
    if [[ $(grep -i -x $word /usr/share/dict/words) ]]
    then
        echo "$word is spelled correctly"
    else
        echo "$word is spelled incorrectly"
    fi
done
