#!/bin/bash

threshold=$1

#take a look at results
logFileName=`grep "\[WARNING\] No default gLogFilename string value. Log data will be written in" "temp$timeStamp" | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 
parameter=${logFileName#*/datalog_}
activeCount=`grep " : activeCount" $logFileName | tail -n 1 | sed -r -e "s/[0-9]+ : activeCount //"`

echo $activeCount

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
fi
rm $logFileName
rm "logs/properties_$parameter"
rm "temp$timeStamp"
