#!/bin/bash

password=$1
timeStamp=$2
gateLogin=$3
gateTown=$4
hostname=`hostname`

touch communication$timeStamp
oldest=0

while [ $oldest = "0" ] || [ -e communicationInProgress ]
do
	othersWaiting=`ls communication*[0-9]`
	oldest=1
	for instance in $othersWaiting
	do
		instanceTimeStamp=${instance#communication}
		if [ $instanceTimeStamp -lt $timeStamp ]
		then
			oldest=0
			break
		fi
	done
	echo "wait for communication"
	sleep 10
done

#while [ -e communicationInProgress ]
#do
#	sleep 10
#	echo "wait for communication"
#done
touch communicationInProgress

 
./sshConnect.sh $gateLogin access.$gateTown.grid5000.fr $password "./buildTunnelToLri.sh $hostname" | tee test
port=$(egrep "^[0-9]+.$" test)
port=${port:0:${#port}-1}
echo $port
./buildTunnelToAccess.sh $gateLogin access.$gateTown.grid5000.fr $port $password
