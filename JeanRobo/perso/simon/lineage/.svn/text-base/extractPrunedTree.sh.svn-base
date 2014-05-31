

#!/bin/bash

start=$1
end=$2
filename=$3

if [ ! -d "trees" ]; then
	mkdir trees
	echo "make \"./trees\" to store all trees extracted."
	echo "---"
	echo
	echo
	echo
	echo
	echo
	echo
fi

./toNewick.py -F $filename -B $start -E $end -N 2
 
