#!/bin/bash

threshold=$1
remoteDir=$2
remoteDirDiscarded=$3

#take a look at results
logFileName=`grep "\[WARNING\] No default gLogFilename string value. Log data will be written in" "temp$timeStamp" | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 
parameter=${logFileName#*/datalog_}
activeCount=`grep " : activeCount" $logFileName | tail -n 1 | sed -r -e "s/[0-9]+ : activeCount //"`

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

if (( $activeCount == "0" ))
then
	if [ -e "extinguish$mainTimeStamp" ]
	then
		count=$(cat	"extinguish$mainTimeStamp")
		count=$((count+1))
		echo $count > "extinguish$mainTimeStamp"
	else
		echo "1" > "extinguish$mainTimeStamp"
	fi
else
	if [ ! -e "extinguish$mainTimeStamp" ]
	then
		echo "0" > "extinguish$mainTimeStamp"
	fi
fi

completed=$(cat "complete$mainTimeStamp")
extinguished=$(cat "extinguish$mainTimeStamp")
name=$(cat /etc/hostname)

echo "$name : $completed($extinguished)"

rm "take$mainTimeStamp" 

rm $logFileName
rm "logs/properties_$parameter"
rm "temp$timeStamp"
