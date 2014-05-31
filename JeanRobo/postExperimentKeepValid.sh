#!/bin/bash

threshold=$1

#take a look at results
logFileName=`grep -a "\[WARNING\] No default gLogFilename string value. Log data will be written in" "temp$timeStamp" | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 
parameter=${logFileName#*/datalog_}

if [ `perl -ne 'print "$.\n" if /\x00/;' $logFileName | wc -l` -gt 0 ]
then 
	echo "NULL character in $logFileName. This file won't be taken into account." 
else
	activeCount=`grep -a " : activeCount" $logFileName | tail -n 1 | sed -r -e "s/[0-9]+ : activeCount //"`

	#transmit log file if necessary
	if (( $activeCount > $threshold ))
	then
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
	else
		count=$(cat	"complete$mainTimeStamp")
		rm $logFileName
		rm "logs/properties_$parameter"
	fi
	echo "Done : $count/$nbExp"
fi
rm "temp$timeStamp"
rm "temp"$timeStamp"Error"
