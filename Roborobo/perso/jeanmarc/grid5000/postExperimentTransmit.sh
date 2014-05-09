#!/bin/bash

gateTown=`sed -n 1p $1`
password=`sed -n 2p $1`
login=`sed -n 4p $1`
localPass=`sed -n 5p $1`
gateLogin=`sed -n 6p $1`
threshold=$2
remoteDir=$3
hostname=`hostname`

if [ ! -e "./extinguishCount$mainTimeStamp" ]
then
	touch "take$mainTimeStamp" 
	echo "0" > "extinguishCount$mainTimeStamp"
	rm "take$mainTimeStamp" 
fi


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
		./prepareTunnels.sh $password $timeStamp $gateLogin $gateTown
		./transmitMnemosyne.sh $logFileName $remoteDir $login $localPass 
		./transmitMnemosyne.sh "logs/properties_$parameter" $remoteDir $login $localPass> /dev/null 
		./destroyTunnels.sh $password $timeStamp
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
		touch "take$mainTimeStamp" 
		extinguish=$(cat "extinguishCount$mainTimeStamp")	
		extinguish=$((extinguish+1))
		echo $extinguish > "extinguishCount$mainTimeStamp"
		count=$(cat	"complete$mainTimeStamp")
		rm "take$mainTimeStamp" 
	fi
	echo "$hostname Done : $count/$nbExp ($extinguish)"
fi
rm $logFileName
rm "logs/properties_$parameter"
rm "temp$timeStamp"
