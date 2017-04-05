#!/bin/bash

#stores file into variable
input=`cat`

#loop through each character and XOR
if [ "$1" = "-f" ]
then
    while read -r -n1 char    
    do
        s+=char^42
    done
fi

#!/bin/sh
dir=$1
RESULT=`ls -Fa $dir | grep -v [/@] | sed 's/\*$//g' \
| sed -e "s/^/.\//g" `
IFS='
'
cd $dir
for FILE1 in $RESULT
do
    if [ -r "$FILE1" ]
    then



