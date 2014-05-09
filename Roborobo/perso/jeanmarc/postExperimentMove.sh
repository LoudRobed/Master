#!/bin/bash

dest=$1

#take a look at results
logFileName=`grep -a "\[WARNING\] No default gLogFilename string value. Log data will be written in" "temp$timeStamp" | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 
parameter=${logFileName#*/datalog_}

if [ `perl -ne 'print "$.\n" if /\x00/;' $logFileName | wc -l` -gt 0 ]
then 
	echo "NULL character in $logFileName. This file won't be taken into account." 
else
	param=${logFileName#*_}
	mv logs/properties_$param $dest
	mv $logFileName $dest

	#wait until can update the results
	while [ -e "take$mainTimeStamp" ]
	do
		sleep 1
	done
	#update results
	touch "take$mainTimeStamp" 
	count=$(cat	"complete$mainTimeStamp")
	count=$((count+1))
	echo $count > "complete$mainTimeStamp"
	rm "take$mainTimeStamp" 
	echo "Done : $count/$nbExp"
fi
rm "temp$timeStamp"
rm "temp"$timeStamp"Error"
