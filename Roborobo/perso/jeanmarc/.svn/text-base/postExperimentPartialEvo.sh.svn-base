#!/bin/bash

#get the name of the log file
logFileName=`grep "\[WARNING\] No default gLogFilename string value. Log data will be written in" "temp$timeStamp" | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 

here=`pwd`

#trace the altruismCost curve
cd ../../Perso/Jeanmarc/dev/script/work/MedeaAltruism/
./runAltruisticMeasure.sh $here"/"$logFileName

#extract median from the last printed line
lastLine=`tail -n 1 tmp.dat`
arr=(`echo $lastLine | tr ',' ' '`)
medianAltruismCost=${arr[4]}
cd $here

#extract last active count
activeCount=`grep "active count" $logFileName | tail -n 1`
activeCount=${activeCount#* : active count is}

#extract movement quantity
movQu=`grep "movQu" $logFileName | tail -n 1`
movQu=${movQu#* : movQu}

#print stuff in the file
echo "$movQu,$activeCount,$medianAltruismCost" >> resultPartialEvo.txt

storageDir=~/Resultats/1010-mEDEA-Altruism/dynamicHarvesting/301210-ReplayPartialEvo-Lag200/

mv $logFileName $storageDir 
parameter=${logFileName#*/datalog_}
mv "logs/properties_$parameter" $storageDir 
mv "logs/altruisticMeasure_$parameter.eps" $storageDir 
rm logs/extract.dat

rm "temp$timeStamp"
