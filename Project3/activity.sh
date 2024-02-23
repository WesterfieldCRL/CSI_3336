#!/bin/bash

# file: activity.sh
# author: Wesely Anastasi
# course: CSI 3336
# due date: 2/13/2024
#
# date modified: 2/13/2024
# - File Created
#
# This script reports the number of files in a directory that have been modified in the last 24 hours, the last 7 days, and longer than 7 days ago.

if [[ $# -eq 0 ]]
then
    >&2 echo "Usage: $0 <folder_path>"
    exit 1
fi

if [[ ! -d $1 ]]
then
    >&2 echo "Error: $1 is not a directory"
    exit 1
fi

activeFileSize=0
recentFileSize=0
idleFileSize=0
numActiveFiles=0
numRecentFiles=0
numIdleFiles=0

for file in $(find $1 -type f)
do 
    if [[ $(stat -c %Y $file) -gt $(date -d "now - 1 day" +%s) ]] #If file was modified in the last 24 hours
    then
        activeFileSize=$(($activeFileSize + $(stat -c %s $file)))
        numActiveFiles=$(($numActiveFiles + 1))
    elif [[ $(stat -c %Y $file) -gt $(date -d "now - 7 day" +%s) ]] #If file was modified in the last 7 days
    then
        recentFileSize=$(($recentFileSize + $(stat -c %s $file)))
        numRecentFiles=$(($numRecentFiles + 1))
    else #If file was modified more than 7 days ago
        idleFileSize=$(($idleFileSize + $(stat -c %s $file)))
        numIdleFiles=$(($numIdleFiles + 1))
    fi
done

echo "active: $numActiveFiles ($activeFileSize bytes)"
echo "recent: $numRecentFiles ($recentFileSize bytes)"
echo "idle: $numIdleFiles ($idleFileSize bytes)"