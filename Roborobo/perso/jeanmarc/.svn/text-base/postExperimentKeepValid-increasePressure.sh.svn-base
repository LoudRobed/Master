#!/bin/bash

threshold=$1
remoteDir=$2
hostname=`hostname`

#take a look at results
logFileName=`grep -a "\[WARNING\] No default gLogFilename string value. Log data will be written in" "temp$timeStamp" | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 
parameter=${logFileName#*/datalog_}

if [ `perl -ne 'print "$.\n" if /\x00/;' $logFileName | wc -l` -gt 0 ]
then 
	echo "NULL character in $logFileName. This file won't be taken into account." 
else
	activeCount=`grep -a " : activeCount" $logFileName | tail -n 1 | sed -r -e "s/[0-9]+ : activeCount //"`
	pressure=`grep -a " : P " $logFileName | tail -n 1 | sed -r -e "s/[0-9]+ : P //"` 
	lastIteration=`tail -n 1 $logFileName | sed -r -e "s/ :.*//"`

	#transmit log file if necessary
	if (( $lastIteration > $threshold ))
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
		extinguish=$(cat "extinguishCount$mainTimeStamp")	
		rm "take$mainTimeStamp" 
	else
		rm $logFileName
		rm "logs/properties_$parameter"
		for file in logs/extract*_$parameter.dat ; do echo $file ; rm $file ; done

		touch "take$mainTimeStamp" 
		extinguish=$(cat "extinguishCount$mainTimeStamp")	
		extinguish=$((extinguish+1))
		echo $extinguish > "extinguishCount$mainTimeStamp"
		count=$(cat	"complete$mainTimeStamp")
		rm "take$mainTimeStamp" 
	fi
        echo "$hostname lastIteration : $lastIteration"
        echo "$hostname pressure : $pressure"
	echo "$hostname Done : $count/$nbExp ($extinguish)"
fi
rm "temp$timeStamp"
