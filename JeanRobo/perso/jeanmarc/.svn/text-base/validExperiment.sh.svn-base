#! /bin/sh
if [ ! $# -eq 2 ]
then
	echo "USAGE: ./goRoborobo NB_OF_EXP CONFIG_FILE"
else
	successCnt=1
	totCnt=0
	while (( $successCnt <= $1 )) 
	do
		echo =-=-=-=-=-=
		echo Exp. $successCnt of $1
		echo =-=-=-=-=-=
		./roborobo -l $2 | tee "temp"
		echo -
		totCnt=$((totCnt+1))

		logFileName=`grep "\[WARNING\] No default gLogFilename string value. Log data will be written in" temp | sed -e "s/\[WARNING\] No default gLogFilename string value. Log data will be written in //" | sed -e "s/\"//g"` 
		parameter=${logFileName#*/datalog_}
		activeCount=`grep "active count" $logFileName | tail -n 1 | sed -r -e "s/[0-9]+ : active count is //"`

		if (( $activeCount > 50 ))
		then
			successCnt=$((successCnt+1))
		else
			rm $logFileName
			rm "logs/properties_$parameter"
		fi

	done

	echo =-=-=-=-=-=
	echo "Success rate : $((successCnt-1))/$totCnt"
	echo =-=-=-=-=-=

fi
